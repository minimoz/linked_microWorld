/**
* moz
*/

#include				"AEntity.hpp"

AEntity::AEntity() {
}


AEntity::~AEntity() {
}

const int				AEntity::getId() const {
	return (_id);
}

sf::Sprite				*AEntity::getSprite() {
	return (&_sprite);
}

const sf::Transform		&AEntity::getTransform() {
	return (_transform);
}

const std::string		&AEntity::getImgName() {
	return (_imgName);
}

const sf::Color			&AEntity::getColor() {
	return (_sprite.getColor());
}

void					AEntity::setSprite(const sf::Sprite &sprite) {
	_sprite = sprite;
}

void					AEntity::setTransform(const sf::Transform &transform) {
	_transform = transform;
}

void					AEntity::setImgName(const std::string &imgName) {
	_imgName = imgName;
}

int						AEntity::getRandomNb(int min, int max) {
	return (((double(std::rand()) / double(RAND_MAX) * (max - min)) + min));
}

void					AEntity::draw(sf::RenderWindow *window) {
	window->draw(_sprite/*, _map.at(i)->getTransform()*/);
}
