/**
 * moz
 */

#include									"Map.hpp"
#include									"Tile.hpp"
#include									"PersonBody.hpp"
#include									"MapGenerator.hpp"

Map::Map() {
  _width = WIDTH_DEFAULT_;
  _height = HEIGHT_DEFAULT_;
}

Map::Map(int width, int height) {
	_width = width;
	_height = height;
}

Map::~Map() {
}

void										Map::toString() {
	for (std::vector<std::shared_ptr<Tile> >::iterator it = _tileMap.begin(); it != _tileMap.end(); ++it) {
		if ((it - _tileMap.begin()) % _width == 0) {
			std::cout << std::endl;
		}
		(*it)->toString();
	}
}

int											Map::getWidth() const {
	return (_width);
}

int											Map::getHeight() const {
	return (_height);
}

const std::vector<std::shared_ptr<Tile>>	&Map::getMap() {
	return (_tileMap);
}

std::shared_ptr<Tile>						Map::getTile(int x, int y) {
	return (_tileMap.at(convertDblDimToSmpDim(x, y)));
}

std::shared_ptr<Tile>						Map::getTile(int coord) {
	return (_tileMap.at(coord));
}

const std::pair<int, int>					Map::convertSmpDimToDblDim(int pos) {
	return (std::pair<int, int>(pos % _width, (pos - (pos % _width)) / _width));
}

int											Map::convertDblDimToSmpDim(int x, int y) {
	return (y * _width + x);
}

int											Map::distance(int x1, int y1, int x2, int y2) {
	return (abs(x1 - x2) + abs(y1 - y2));
}

int											Map::distance(int coord1, int coord2) {
	std::pair<int, int>						pair1 = convertSmpDimToDblDim(coord1);
	std::pair<int, int>						pair2 = convertSmpDimToDblDim(coord2);

	return (distance(pair1.first, pair1.second, pair2.first, pair2.second));
}

void										Map::init() {
	MapGenerator							*mapGenerator = new MapGenerator(_width, _height);

	std::cout << "Width: " << _width << std::endl;
	std::cout << "Height: " << _height << std::endl;

	mapGenerator->generate(_tileMap);

	//std::cout << sizeof((*_map[99])) << std::endl;
}

void										Map::update() {
	for (std::vector<std::shared_ptr<Tile> >::iterator it = _tileMap.begin(); it != _tileMap.end(); ++it) {
		_tileMap.at((*it)->getId())->getSprite()->setColor(sf::Color::White);
	}
}

void										Map::draw(sf::RenderWindow *window) {
	for (std::vector<std::shared_ptr<Tile> >::iterator it = _tileMap.begin(); it != _tileMap.end(); ++it) {
		(*it)->draw(window);
	}
}

void										Map::setPersonOnTile(int x, int y, const std::shared_ptr<PersonBody> &personBody) {
	_tileMap.at(convertDblDimToSmpDim(x, y))->setPersonBody(personBody);
}

void										Map::deletePersonOnTile(int x, int y) {
	_tileMap.at(convertDblDimToSmpDim(x, y))->deletePersonBody();
}