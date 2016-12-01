/**
 * moz
 */

#ifndef									TILE_HPP__
# define								TILE_HPP__

# include								<iostream>
# include								<memory>

# include								<SFML/Graphics.hpp>

# include								"AEntity.hpp"

# define								WATER_RANGE_	-0.2
# define								GROUND_RANGE_	0.3
# define								HILL_RANGE_		0.4

class									PersonBody;
class									AEntity;
class									APrimaryItem;

enum									_EType {
	Water = -1,
	Ground,
	Hill,
	Mountain
};

// Aprimary herite de Iitem et concerne les resources principales (water + food)
// Aprimary contient :
//		un pointer sur fonction sur la fonction PersonBody::setToto
//		une quantité de resource
// class Water et Food herite de Aprimary

class									Tile : public AEntity {
private:
	std::shared_ptr<PersonBody>			_personBody;
	double								_noise;
	int									_altitude;
	float								_temperature;
	float								_humidity;
	bool								_isTransparent;
	bool								_isPassable;
	_EType								_tileType;
	std::vector<APrimaryItem>			_primaryItems;
	//std::vector<ASecondaryItem>		_secondaryItems;

public:
	Tile();
	Tile(const std::string &, int);
	Tile(double, int);
	~Tile();

	void								toString();
	const std::shared_ptr<PersonBody>	&getPersonBody();
	int									getAltitude();
	const bool							&isTransparent();
	const bool							&isPassable();
	const _EType						&getTileType();
	const std::vector<APrimaryItem>		&getPrimaryItems();
	//const std::vector<ASecondaryItem>	&getASecondaryItems();
	void								setPersonBody(const std::shared_ptr<PersonBody> &);

	void								init();
	void								deletePersonBody();
	void								setPosition(const std::pair<int, int> &);
	void								setColor(int, int, int, int);
	void								calculateTile();
};

#endif									/* TILE_HPP__ */
