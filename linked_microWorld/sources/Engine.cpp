/**
 * moz
 */

#include														"Engine.hpp"
#include														"Map.hpp"
#include														"AEntity.hpp"
#include														"PersonBody.hpp"
#include														"ResourceManager.hpp"

//#include														"Tile.hpp"

Engine::Engine() :	_map(std::unique_ptr<Map>(new Map(100, 50))),
					_speed(GAME_SPEED_) {
	_heures = 0;
	_personsCpt = 0;
}

Engine::~Engine() {
}

void															Engine::init() {
	std::srand(std::time(NULL));

	_window.create(sf::VideoMode(_map->getWidth() * TILE_SIZE_, _map->getHeight() * TILE_SIZE_), WINDOW_TITLE_, sf::Style::Titlebar | sf::Style::Close);
	_window.setFramerateLimit(60);

	_map->init();

	addPerson();

	addText(FONT_PATH_ FONT_NAME_, "date", "0 h", 24, sf::Color::Black);
	getText("date")->setStyle(sf::Text::Bold);
	getText("date")->setPosition(10, 10);
}

void															Engine::launch() {
	while (_window.isOpen()) {

		sf::Event												event;
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

void															Engine::update() {
	getText("date")->setString(std::to_string(_heures % 24) + " hour" + (_heures <= 1 ? "" : "s") + (_heures / 24 == 0 ? "" : (", " + std::to_string(_heures / 24) + " day" + (_heures / 24 <= 1 ? "" : "s"))));

	_map->update();

	checkPersonsLifes();

	for (std::vector<std::shared_ptr<PersonBody> >::iterator it = _persons.begin(); it != _persons.end(); ++it) {
		_map->deletePersonOnTile((*it)->getX(), (*it)->getY());
		(*it)->update(_map->getWidth(), _map->getHeight());
		_map->setPersonOnTile((*it)->getX(), (*it)->getY(), (*it));
	}

	++_heures;
}

void															Engine::draw() {
	_map->draw(&_window);

	for (std::vector<std::shared_ptr<PersonBody> >::iterator it = _persons.begin(); it != _persons.end(); ++it) {
		//(*it)->toString();
		(*it)->draw(&_window);
	}

	for (std::vector<std::pair<std::string, sf::Text *> >::iterator it = _texts.begin(); it != _texts.end(); ++it) {
		_window.draw(*(it->second));
	}
}

void															Engine::addPerson() {
	_persons.emplace_back(std::shared_ptr<PersonBody>(new PersonBody(_map, _personsCpt)));
	_persons.back()->init();
	_persons.back()->initPos();
	_map->setPersonOnTile(_persons.back()->getX(), _persons.back()->getY(), _persons.back());
	++_personsCpt;
}

void															Engine::checkPersonsLifes() {
	for (std::vector<std::shared_ptr<PersonBody> >::iterator	it = _persons.begin(); it != _persons.end(); ) {
		if (_persons.size() && ((*it)->getHunger() == 0 || (*it)->getThirst() == 0)) {
			// create a class corpse
			it = _persons.erase(it);
		} else {
			++it;
		}
	}
}

void															Engine::addText(std::string font, std::string id, std::string str, int size, sf::Color color) {
	sf::Text													*text = new sf::Text();

	text->setFont(*ResourceManager::getInstance()->getFont(font));
	text->setString(str);
	text->setCharacterSize(size);
	text->setColor(color);

	_texts.emplace_back(std::pair<std::string, sf::Text *>(id, text));
}

sf::Text														*Engine::getText(std::string id) {
	for (std::vector<std::pair<std::string, sf::Text *> >::iterator it = _texts.begin(); it != _texts.end(); ++it) {
		if (it->first == id) {
			return (it->second);
		}
	}
}

void															Engine::rmText(std::string id) {
	for (std::vector<std::pair<std::string, sf::Text *> >::iterator it = _texts.begin(); it != _texts.end(); ++it) {
		if (it->first == id) {
			_texts.erase(it);
		}
	}
}