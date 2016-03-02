/**
 * moz
 */

#ifndef									TILE_HPP__
# define								TILE_HPP__

# include								<iostream>
# include								<memory>

# include								<SFML/Graphics.hpp>

# include								"AEntity.hpp"

class PersonBody;
class ResourceManager;
class AEntity;

class									Tile : public AEntity {
private:
	std::shared_ptr<PersonBody>			_personBody;
	bool								_isTransparent;
	bool								_isPassable;

public:
	Tile();
	Tile(const std::string &, int);
	~Tile();

	void								toString();
	const std::shared_ptr<PersonBody>	&getPersonBody();
	const bool							&isTransparent();
	const bool							&isPassable();
	void								setPersonBody(const std::shared_ptr<PersonBody> &);

	void								init();
	void								deletePersonBody();
	void								setPosition(const std::pair<int, int> &);
	void								setColor(int);
};

#endif									/* TILE_HPP__ */
