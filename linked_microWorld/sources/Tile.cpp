/**
 * moz
 */

#include							"Tile.hpp"
# include							"ResourceManager.hpp"

Tile::Tile() :	_personBody(nullptr) {
	_id = -1;
	_imgName = PATH_IMAGES_ "grass.png";
	_isTransparent = true;
	_isPassable = true;
}

Tile::Tile(const std::string &imgName, int id) : _personBody(nullptr) {
	_id = id;
	_imgName = PATH_IMAGES_ + imgName;
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

const bool							&Tile::isTransparent() {
	return (_isTransparent);
}

const bool							&Tile::isPassable() {
	return (_isPassable);
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

void								Tile::setColor(int color) {
	/*s_color							hexColor;

	hexColor.red = (color & 0xff000000) >> 24;
	hexColor.green = (color & 0x00ff0000) >> 16;
	hexColor.blue = (color & 0x0000ff00) >> 8;
	hexColor.alpha = (color & 0x000000ff);*/

	_sprite.setColor(sf::Color(color));
}
