/**
 * moz
 */

#include							"Tile.hpp"
#include							"ResourceManager.hpp"
#include							"APrimaryItem.hpp"

Tile::Tile() :	_personBody(nullptr) {
	_id = -1;
	_imgName = PATH_IMAGES_ "ground_sprite.png";
	_noise = 0;
	_altitude = 0;
	_temperature = 0.0;
	_humidity = 0.0;
	_isTransparent = true;
	_isPassable = true;
}

Tile::Tile(const std::string &imgName, int id) : _personBody(nullptr) {
	_id = id;
	_imgName = PATH_IMAGES_ + imgName;
	_noise = 0;
	_altitude = 0;
	_temperature = 0.0;
	_humidity = 0.0;
	_isTransparent = true;
	_isPassable = true;
}

Tile::Tile(double noise, int id) : _personBody(nullptr) {
	_id = id;
	_imgName = PATH_IMAGES_ "ground_sprite.png";
	_noise = noise;
	_altitude = 0;
	_temperature = 0.0;
	_humidity = 0.0;
	_isTransparent = true;
	_isPassable = true;
}

Tile::~Tile() {
  // delete
}

void								Tile::toString() {
	std::cout << (_personBody != nullptr ? "1" : "0");
}

const std::shared_ptr<PersonBody>	&Tile::getPersonBody() {
	return (_personBody);
}

int									Tile::getAltitude() {
	return (_altitude);
}

const bool							&Tile::isTransparent() {
	return (_isTransparent);
}

const bool							&Tile::isPassable() {
	return (_isPassable);
}

const _EType						&Tile::getTileType() {
	return (_tileType);
}

const std::vector<APrimaryItem>		&Tile::getPrimaryItems() {
	return (_primaryItems);
}

void								Tile::setPersonBody(const std::shared_ptr<PersonBody> &personBody) {
	_personBody = personBody;
}

void								Tile::init() {
	_sprite.setTexture(*ResourceManager::getInstance()->getTexture(_imgName));
}

void								Tile::deletePersonBody() {
	_personBody = nullptr;
}

void								Tile::setPosition(const std::pair<int, int> &coord) {
	_sprite.setPosition(coord.first * TILE_SIZE_, coord.second * TILE_SIZE_);
}

void								Tile::setColor(int r, int g, int b, int a) {
	/*s_color							hexColor;

	hexColor.red = (color & 0xff000000) >> 24;
	hexColor.green = (color & 0x00ff0000) >> 16;
	hexColor.blue = (color & 0x0000ff00) >> 8;
	hexColor.alpha = (color & 0x000000ff);*/

	_sprite.setColor(sf::Color(r, g, b, a));
}

// map _noise that is from -1 to 1 to an altitude
// CREATE CLASS A* TO FIND SHORTEST PATH BETWEEN 2 POINTS
void								Tile::calculateTile() {
	if (_noise < WATER_RANGE_) {
		_altitude = -1;
		_isTransparent = true;
		_isPassable = false;
		_sprite.setTextureRect(sf::IntRect(0, TILE_SIZE_ * 0, TILE_SIZE_, TILE_SIZE_));
	} else if (_noise < GROUND_RANGE_) {
		_altitude = 0;
		_isTransparent = true;
		_isPassable = true;
		_sprite.setTextureRect(sf::IntRect(0, TILE_SIZE_ * 1, TILE_SIZE_, TILE_SIZE_));
	} else if (_noise < HILL_RANGE_) {
		_altitude = 1;
		_isTransparent = true;
		_isPassable = true;
		_sprite.setTextureRect(sf::IntRect(TILE_SIZE_ * 6, TILE_SIZE_ * 2, TILE_SIZE_, TILE_SIZE_));
	} else {
		_altitude = 2;
		_isTransparent = false;
		_isPassable = false;
		_sprite.setTextureRect(sf::IntRect(TILE_SIZE_ * 9, TILE_SIZE_ * 3, TILE_SIZE_, TILE_SIZE_));
	}

	_tileType = static_cast<_EType>(_altitude);
}