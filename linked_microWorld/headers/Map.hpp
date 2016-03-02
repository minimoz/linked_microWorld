/**
 * moz
 */

#ifndef											MAP_HPP__
# define										MAP_HPP__

# include										<iostream>
# include										<vector>
# include										<memory>

# include										<SFML/Graphics.hpp>

# define										WIDTH_DEFAULT_	50
# define										HEIGHT_DEFAULT_	50

class Tile;
class PersonBody;

class											Map {

private:
	int											_width;
	int											_height;
	std::vector<std::shared_ptr<Tile> >			_tileMap;

public:
	Map();
	Map(int, int);
	~Map();

	void										toString();

	int											getWidth() const;
	int											getHeight() const;
	const std::vector<std::shared_ptr<Tile>>	&getMap();
	std::shared_ptr<Tile>						getTile(int, int);
	std::shared_ptr<Tile>						getTile(int);

	const std::pair<int, int>					convertSmpDimToDblDim(int);
	int											convertDblDimToSmpDim(int, int);

	void										init();
	void										update();
	void										draw(sf::RenderWindow *);
	void										setPersonOnTile(int, int, const std::shared_ptr<PersonBody> &);
	void										deletePersonOnTile(int, int);

private:
	bool										isPersonDead(const std::shared_ptr<PersonBody> &);


};

#endif											/* MAP_HPP__ */
