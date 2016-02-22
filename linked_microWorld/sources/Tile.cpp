/**
 * moz
 */

#include				"../headers/Tile.hpp"

Tile::Tile() {
	_imgName = PATH_IMAGES_ "grass.png";
}

Tile::Tile(const std::string &imgName) {
	_imgName = PATH_IMAGES_ + imgName;
}

Tile::~Tile() {
  // delete
}

int						Tile::init() {
	_sprite.setTexture(*ResourceManager::getInstance()->getTexture(_imgName));
	return (1);
}

void					Tile::setPosition(const std::pair<int, int> &coord) {
	_sprite.setPosition(coord.first * TILE_SIZE_, coord.second * TILE_SIZE_);
}
