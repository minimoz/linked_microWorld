/**
 * moz
 */

#include					"../headers/Map.hpp"

Map::Map() {
  _width = WIDTH_DEFAULT_;
  _height = HEIGHT_DEFAULT_;
}

Map::Map(const int &width, const int &y) {
	_width = width;
	_height = y;
}

Map::~Map() {
}

const int&					Map::getWidth() {
	return (_width);
}

const int&					Map::getHeight() {
	return (_height);
}

const std::pair<int, int>&	Map::convertSmpDimToDblDim(const int &pos) {
	//std::pair<int, int>		coord(pos % _x, (pos - (pos % _x)) / _x);

	return (std::pair<int, int>(pos % _width, (pos - (pos % _width)) / _width));
}

int							Map::init() {
	std::cout << "Width: " << _width << std::endl;
	std::cout << "Height: " << _height << std::endl;

	for (int i = 0; i < _width * _height; ++i) {
		std::shared_ptr<Tile> tile(new Tile("grass.png"));
		if (!tile->init())
			return EXIT_FAILURE;
		tile->setPosition(convertSmpDimToDblDim(i));
		_map.push_back(tile);
	}

	addPerson();
	addPerson();
	addPerson();
	addPerson();
	addPerson();
	addPerson();
	addPerson();
	addPerson();
	addPerson();
	addPerson();
	addPerson();
	addPerson();
	addPerson();

	//std::cout << sizeof((*this->_map[99])) << std::endl;

	return (1);
}

void						Map::update() {
	for (std::vector<std::shared_ptr<Person> >::iterator it = _persons.begin(); it != _persons.end(); ++it) {
		(*it)->update(_width, _height);
	}
}

void						Map::draw(sf::RenderWindow *window) {
	for (std::vector<std::shared_ptr<Tile> >::iterator it = _map.begin(); it != _map.end(); ++it) {
		(*it)->draw(window);
	}

	for (std::vector<std::shared_ptr<Person> >::iterator it = _persons.begin(); it != _persons.end(); ++it) {
		(*it)->draw(window);
	}

	//for (int i = 0; i < _map.size(); ++i) {
	//	window->draw(_map.at(i)->getSprite()/*, _map.at(i)->getTransform()*/);
	//}
}

int							Map::addPerson() {
	std::shared_ptr<Person>	person(new Person());
	if (!person->init())
		return EXIT_FAILURE;
	person->initPos(_width, _height);
	_persons.push_back(person);

	return (1);
}

bool						Map::isAnyPersonOnTile(const int &x, const int &y) {
	for (std::vector<std::shared_ptr<Person> >::iterator it = _persons.begin(); it != _persons.end(); ++it) {
		if ((*it)->getX() == x && (*it)->getY() == y)
	}
}