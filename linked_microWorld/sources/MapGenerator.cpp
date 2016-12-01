/**
* moz
*/

#include									"MapGenerator.hpp"
#include									"Tile.hpp"

MapGenerator::MapGenerator(int width, int height) {
	_width = width;
	_height = height;
}

MapGenerator::~MapGenerator() {
	// delete
}

void										MapGenerator::toString() {
}

const std::pair<int, int>					MapGenerator::convertSmpDimToDblDim(int pos) {
	return (std::pair<int, int>(pos % _width, (pos - (pos % _width)) / _width));
}

int											MapGenerator::convertDblDimToSmpDim(int x, int y) {
	return (y * _width + x);
}

double										MapGenerator::findNoise(double x, double y) {
	int n = (int)x + (int)y * SEED_;
	//int n = (int)x + (int)y * 57;
	n = (n << 13) ^ n;
	int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

	return (1.0 - ((double)nn / 1073741824.0));
}

double										MapGenerator::smoothNoise(double x, double y) {
	double corners;
	double sides;
	double center;

	corners = (findNoise(x - 1.0, y - 1.0) + findNoise(x + 1.0, y - 1.0) + findNoise(x - 1.0, y + 1.0) + findNoise(x + 1.0, y + 1.0)) / 16.0;
	sides = (findNoise(x - 1.0, y) + findNoise(x + 1.0, y) + findNoise(x, y - 1.0) + findNoise(x, y + 1.0)) / 8.0;
	center = findNoise(x, y) / 4.0;

	return (corners + sides + center);
}

double										MapGenerator::interpolate(double a, double b, double x) {
	double ft = x * 3.1415927;			// x * Pi
	double f = (1.0 - cos(ft)) * 0.5;

	return (a * (1.0 - f) + b * f);
}

double										MapGenerator::calcNoise(double x, double y) {
	double floorX = (double)((int)x);
	double floorY = (double)((int)y);
	double s, t, u, v;

	/*s = findNoise(floorX, floorY);
	t = findNoise(floorX + 1, floorY);
	u = findNoise(floorX, floorY + 1);
	v = findNoise(floorX + 1, floorY + 1);*/
	
	s = smoothNoise(floorX, floorY);
	t = smoothNoise(floorX + 1, floorY);
	u = smoothNoise(floorX, floorY + 1);
	v = smoothNoise(floorX + 1, floorY + 1);

	double noise1 = interpolate(s, t, x - floorX);
	double noise2 = interpolate(u, v, x - floorX);

	return(interpolate(noise1, noise2, y - floorY));
}

double										MapGenerator::calcAllOctaves(int w, int h, double frequency, double amplitude, int octaves, double lacunarity, double persistence) {
	double									noise = 0.0;

	for (int o = 0; o < octaves; ++o) {
		noise += calcNoise(w * frequency/* / zoom*/, h/* / zoom*/ * frequency) * amplitude;
		frequency *= lacunarity;
		amplitude *= persistence;
	}

	return (noise);
}

void										MapGenerator::generate(std::vector<std::shared_ptr<Tile> > &tileMap) {
	// Define what variables will stand in the file (different kind of tiles, amount in % of each, pattern, range for amount of groups, pictures names)
	// Get map config (all possible tiles, percentage of each) from Map File (map1.map)
	// Create tiles objects (class Grass, class Water(River and Lakes could inheritate from Water), class Mountain, class Peak, class Hill, class Bush)
	// Get number of Tiles for each possible tile in the map
	// For each possible tile get pattern (lake/mountain/peak/hill/bush=>mass, river/mountain/hill=>chain)
	// With the pattern, separate the amount of tiles (for a given possible tile) in a random number (in a range given in the file) of group of tiles
	// For each group display the tiles of the group randomly but following the pattern
	//
	// TAKE CARE TO NOT DISPLAY DIFFERENT GROUPS OF THE SAME KIND OF TILE TOO CLOSE !

	//std::ofstream							myFile(MAP_FILE_);

	double									noise;
	double									frequency = 0.2;
	double									amplitude = 1.0;
	int										octaves = 8;
	double									lacunarity = 2.0;
	double									persistence = 0.5; // lower it to get a smoother result

	for (int h = 0; h < _height; ++h) {
		for (int w = 0; w < _width; ++w) {

			noise = calcAllOctaves(w, h, frequency, amplitude, octaves, lacunarity, persistence);
			/*if (myFile.is_open()) {
				myFile << (int)(noise * 10) << "\t";
				//myFile << noise << "\t";
			}*/

			std::shared_ptr<Tile> tile(new Tile(noise, convertDblDimToSmpDim(w, h))); // later add temperature and humidity
			tile->calculateTile();
			tile->init();
			tile->setPosition(std::pair<int, int>(w, h));

			//int color = (int)((noise * 128.0) + 128.0); // Convert to 0-256 values.
			//if (color > 255)
			//	color = 255;
			//if (color < 0)
			//	color = 0;

			//tile->setColor(color, color, color, 255);
			tileMap.push_back(tile);

		}
		/*if (myFile.is_open()) {
			myFile << std::endl;
		}*/
	}

	/*myFile.close();*/
}