/**
 * moz
 */

#ifndef													ENGINE_HPP__
# define												ENGINE_HPP__

# include												<iostream>
# include												<vector>
# include												<memory>
# include												<cstdlib>
# include												<ctime>
# include												<chrono>
# include												<thread>

# include												<SFML/Graphics.hpp>

# define												WINDOW_TITLE_ "Linked microWorld"
# define												GAME_SPEED_ 250
# define												FONT_NAME_ "Consolas.ttf"

class Map;
class PersonBody;

class													Engine {
private:
	sf::RenderWindow									_window;
	std::vector<std::pair<std::string, sf::Text *> >	_texts;
	std::unique_ptr<Map>								_map;
	std::vector<std::shared_ptr<PersonBody> >			_persons;
	int													_speed;
	int													_heures;
	int													_personsCpt;

public:
	Engine();
	~Engine();

	void												init();
	void												launch();
	void												update();
	void												draw();
	void												addPerson();
	void												checkPersonsLifes();
	void												addText(std::string, std::string, std::string = "", int = 24, sf::Color = sf::Color::Black);
	sf::Text											*getText(std::string);
	void												rmText(std::string);

};

#endif													/* ENGINE_HPP__ */
