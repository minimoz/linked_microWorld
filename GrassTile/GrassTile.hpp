#ifdef COMPILE_GRASS_TILE
# define								GRASS_TILE_EXPORT __declspec(dllexport)
#else
# define								GRASS_TILE_EXPORT __declspec(dllimport) 
# include								"Tile.hpp"
#endif

class									Tile;

class GRASS_TILE_EXPORT GrassTile : public Tile {

public:
	static double						GrassTile_Divide(double a, double b);

};
