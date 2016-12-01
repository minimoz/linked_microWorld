/**
* moz
*/

#ifndef															PERSONSPIRIT_HPP__
# define														PERSONSPIRIT_HPP__

# include														<iostream>
# include														<memory>
# include														<chrono>
# include														<random>

# include														"AEntity.hpp"

class AEntity;
class Map;
class Tile;
class AIv1;

class															PersonSpirit : public AEntity {

private:
	std::unique_ptr<Map>										&_map;
	std::vector<std::shared_ptr<Tile> >							_mapViewFieldPtr;
	std::unique_ptr<AIv1>										_ai;

public:
	//PersonSpirit();
	PersonSpirit(std::unique_ptr<Map> &, int);
	~PersonSpirit();

	const std::unique_ptr<Map>									&getMap();

	void														init();
	std::pair<int, int>											getRandomValidPos();
	bool														isTileInVector(int);
	void														getMapViewField(int, int, int);
	std::pair<int, int>											getDest(int, int, int);

	virtual const int											getX() const = 0;
	virtual const int											getY() const = 0;
	virtual const int											getHunger() const = 0;
	virtual const int											getThirst() const = 0;

	//bool														isAnyPersonOnTile(int, int);
};

#endif															/* PERSONSPIRIT_HPP__ */
