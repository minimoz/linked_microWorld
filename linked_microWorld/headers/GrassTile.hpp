/**
* moz
*/

#ifndef									GRASS_TILE_HPP__
# define								GRASS_TILE_HPP__

# include								<iostream>

# include								"Tile.hpp"

class									Tile;

class									GrassTile : public Tile {

private:

public:
	GrassTile(double, int);
	~GrassTile();

};

#endif									/* GRASS_TILE_HPP__ */
