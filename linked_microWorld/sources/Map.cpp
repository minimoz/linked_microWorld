/**
 * moz
 */

#include									"Map.hpp"
#include									"Tile.hpp"
#include									"PersonBody.hpp"

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

void										Map::init() {
	std::cout << "Width: " << _width << std::endl;
	std::cout << "Height: " << _height << std::endl;

	for (int i = 0; i < _width * _height; ++i) {
		std::shared_ptr<Tile> tile(new Tile("grass.png", i));
		tile->init();
		tile->setPosition(convertSmpDimToDblDim(i));
		_tileMap.push_back(tile);
	}

	//std::cout << sizeof((*this->_map[99])) << std::endl;
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