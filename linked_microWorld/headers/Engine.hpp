/**
 * moz
 */

#ifndef										ENGINE_HPP__
# define									ENGINE_HPP__

# define									WINDOW_TITLE_ "Linked microWorld"

# include									<iostream>
# include									<vector>
# include									<memory>
# include									<cstdlib>
# include									<ctime>
# include									<chrono>
# include									<thread>

# include									<SFML/Graphics.hpp>

# include									"Map.hpp"

class										Engine {
private:
	sf::RenderWindow						_window;
	Map										*_map;
	int										_speed;

public:
	Engine();
	Engine(Map*);
	~Engine();

	int										init();
	void									launch();

};

#endif										/* ENGINE_HPP__ */
