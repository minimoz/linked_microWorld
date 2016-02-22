/**
 * moz
 */

#include			"../headers/Person.hpp"

Person::Person() {
	_id = getRandomNb(10, 99);
	_x = 0;
	_y = 0;
}

Person::~Person() {
	// delete
}

int					Person::getX() {
	return (_x);
}

int					Person::getY() {
	return (_y);
}

int					Person::init() {
	_sprite.setTexture(*ResourceManager::getInstance()->getTexture(PATH_IMAGES_ "person.png"));
	return (1);
}

void				Person::initPos(const int &mapWith, const int &mapHeight) {
	_x = getRandomNb(0, mapWith);
	_y = getRandomNb(0, mapHeight);
}

void				Person::update(const int &mapWidth, const int &mapHeight) {
	move();

	std::cout << _id << " -> X: " << _x << " Y: " << _y << std::endl;
	_sprite.setPosition(_x * TILE_SIZE_, _y * TILE_SIZE_);
}

void				Person::move() {
	if ()

	_x = getRandomNb(_x - 1, _x + 1);
	_y = getRandomNb(_y - 1, _y + 1);
}