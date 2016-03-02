/**
 * moz
 */

#ifndef											ENGINE_HPP__
# define										ENGINE_HPP__

# define										WINDOW_TITLE_ "Linked microWorld"

# include										<iostream>
# include										<vector>
# include										<memory>
# include										<cstdlib>
# include										<ctime>
# include										<chrono>
# include										<thread>

# include										<SFML/Graphics.hpp>

class Map;
class PersonBody;

class											Engine {
private:
	sf::RenderWindow							_window;
	std::unique_ptr<Map>						_map;
	std::vector<std::shared_ptr<PersonBody> >	_persons;
	int											_speed;

public:
	Engine();
	~Engine();

	void										init();
	void										launch();
	void										update();
	void										draw();
	void										addPerson();
	void										checkPersonsLifes();

};

#endif											/* ENGINE_HPP__ */
