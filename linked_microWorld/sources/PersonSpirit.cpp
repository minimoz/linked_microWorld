/**
* moz
*/

#include					"PersonSpirit.hpp"
#include					"Tile.hpp"
#include					"Map.hpp"
#include					"PersonBody.hpp"
#include					"AIv1.hpp"

//PersonSpirit::PersonSpirit() :	_map(nullptr),
//								_id(getRandomNb(10, 99)) {
//}

PersonSpirit::PersonSpirit(std::unique_ptr<Map> &map, int id) :	_map(map) {
	_id = id;
	_ai = std::unique_ptr<AIv1>(new AIv1(map));
}

PersonSpirit::~PersonSpirit() {
	// delete
}

const std::unique_ptr<Map>	&PersonSpirit::getMap() {
	return (_map);
}

void						PersonSpirit::init() {
}

std::pair<int, int>			PersonSpirit::getRandomValidPos() {
	unsigned				seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::vector<std::shared_ptr<Tile>> map = _map->getMap();

	std::shuffle(map.begin(), map.end(), std::default_random_engine(seed));

	for (std::vector<std::shared_ptr<Tile> >::iterator it = map.begin(); it != map.end(); ++it) {
		if ((*it)->isPassable()) {
			return (_map->convertSmpDimToDblDim((*it)->getId()));
		}
	}

	return (_map->convertSmpDimToDblDim(0));
}

bool						PersonSpirit::isTileInVector(int id) {
	for (std::vector<std::shared_ptr<Tile> >::iterator it = _mapViewFieldPtr.begin(); it != _mapViewFieldPtr.end(); ++it) {
		if ((*it)->getId() == id) {
			return (true);
		}
	}
	return (false);
}

/*
*
* CHECK IF TILE ALREADY PUSH IN MAPVIEWFIELD !!!
*
*/
void						PersonSpirit::getMapViewField(int x, int y, int viewField) {

	if (!isTileInVector(_map->convertDblDimToSmpDim(x, y)) && (_map->getTile(x, y)->isTransparent())) {
		std::shared_ptr<Tile> tile(_map->getTile(x, y));
		_mapViewFieldPtr.push_back(tile);
	}

	if (viewField == 0) {
		return;
	}

	if (y > 0 && _map->getTile(x, y - 1)->isTransparent()) {
		getMapViewField(x, y - 1, viewField - 1);
	}
	if (x < _map->getWidth() - 1 && _map->getTile(x + 1, y)->isTransparent()) {
		getMapViewField(x + 1, y, viewField - 1);
	}
	if (y < _map->getHeight() - 1 && _map->getTile(x, y + 1)->isTransparent()) {
		getMapViewField(x, y + 1, viewField - 1);
	}
	if (x > 0 && _map->getTile(x - 1, y)->isTransparent()) {
		getMapViewField(x - 1, y, viewField - 1);
	}
}

std::pair<int, int>			PersonSpirit::getDest(int x, int y, int viewField) {
	_mapViewFieldPtr.clear();

	getMapViewField(x, y, viewField);

	for (std::vector<std::shared_ptr<Tile> >::iterator it = _mapViewFieldPtr.begin(); it != _mapViewFieldPtr.end(); ++it) {
		((*it)->getSprite())->setColor(sf::Color::Cyan);
	}

	return (_ai->getTargetTile(_mapViewFieldPtr, *this));
}

//bool						PersonSpirit::isAnyPersonOnTile(int x, int y) {
//	for (std::vector<std::shared_ptr<Person> >::iterator it = _persons.begin(); it != _persons.end(); ++it) {
//		if ((*it)->getX() == x && (*it)->getY() == y) {
//			return (true);
//		}
//	}
//
//	return (false);
//}