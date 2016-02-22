/**
 * moz
 */

#include					"../headers/Engine.hpp"

Engine::Engine() {
	_map = new Map();
	_speed = 1000;
}

Engine::Engine(Map* map) {
	_map = map;
	_speed = 1000;
}

Engine::~Engine() {
}

int							Engine::init() {
	std::srand(std::time(NULL));

	_window.create(sf::VideoMode(_map->getWidth() * TILE_SIZE_, _map->getHeight() * TILE_SIZE_), WINDOW_TITLE_, sf::Style::Titlebar | sf::Style::Close);
	_window.setFramerateLimit(60);

	if (!_map->init())
		return EXIT_FAILURE;

	return (1);
}

void						Engine::launch() {
	while (_window.isOpen()) {

		sf::Event		event;
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				_window.close();
		}

		_map->update();

		_window.clear();
		_map->draw(&_window);
		_window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(_speed));
	}
}
