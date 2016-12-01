/**
* moz
*/

#ifndef											MAP_GENERATOR_HPP__
# define										MAP_GENERATOR_HPP__

# include										<vector>
# include										<memory>

# include										<fstream>

# define										MAP_FILE_ "maps/map_test.map"
# define										SEED_ 666666

class Tile;

class											MapGenerator {
private:
	int											_width;
	int											_height;

public:
	MapGenerator(int, int);
	~MapGenerator();

	void										toString();

	const std::pair<int, int>					convertSmpDimToDblDim(int);
	int											convertDblDimToSmpDim(int, int);
	double										findNoise(double, double);
	double										smoothNoise(double, double);
	double										interpolate(double, double, double);
	double										calcNoise(double, double);
	double										calcAllOctaves(int, int, double, double, int, double, double);
	void										generate(std::vector<std::shared_ptr<Tile> > &);
};

#endif											/* MAP_GENERATOR_HPP__ */
