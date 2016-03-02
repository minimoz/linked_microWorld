/**
 * moz
 */

#include					"Engine.hpp"
#include					"Map.hpp"
#include					"AEntity.hpp"
#include					"PersonBody.hpp"

#include					"Tile.hpp"

Engine::Engine() :	_map(std::unique_ptr<Map>(new Map(50, 50))),
					_speed(250) {
}

Engine::~Engine() {
}

void						Engine::init() {
	std::srand(std::time(NULL));

	_window.create(sf::VideoMode(_map->getWidth() * TILE_SIZE_, _map->getHeight() * TILE_SIZE_), WINDOW_TITLE_, sf::Style::Titlebar | sf::Style::Close);
	_window.setFramerateLimit(60);

	_map->init();

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
	addPerson();
	addPerson();
	addPerson();
	addPerson();
}

void						Engine::launch() {
	while (_window.isOpen()) {

		sf::Event		event;
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				_window.close();
		}

		update();

		_window.clear();
		draw();
		_window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(_speed));
	}
}

void						Engine::update() {
	_map->update();

	checkPersonsLifes();

	for (std::vector<std::shared_ptr<PersonBody> >::iterator it = _persons.begin(); it != _persons.end(); ++it) {
		_map->deletePersonOnTile((*it)->getX(), (*it)->getY());
		(*it)->update(_map->getWidth(), _map->getHeight());
		_map->setPersonOnTile((*it)->getX(), (*it)->getY(), (*it));
	}
}

void						Engine::draw() {
	_map->draw(&_window);

	for (std::vector<std::shared_ptr<PersonBody> >::iterator it = _persons.begin(); it != _persons.end(); ++it) {
		(*it)->toString();
		(*it)->draw(&_window);
	}
}

void						Engine::addPerson() {
	_persons.emplace_back(std::shared_ptr<PersonBody>(new PersonBody(_map, _persons.size())));
	_persons.back()->init();
	_persons.back()->initPos(_map->getWidth(), _map->getHeight());
	_map->setPersonOnTile(_persons.back()->getX(), _persons.back()->getY(), _persons.back());
}

void						Engine::checkPersonsLifes() {
	for (std::vector<std::shared_ptr<PersonBody> >::iterator it = _persons.begin(); it != _persons.end(); ) {
		if (_persons.size() && ((*it)->getHunger() == 0 || (*it)->getThirst() == 0)) {
			// create a class corpse

			std::cout << "ID: " << (*it)->getId() << " is dead !" << std::endl;
			it = _persons.erase(it);
		} else {
			++it;
		}
	}
}