/**
* moz
*/

#include										"PathFinding.hpp"
#include										"Tile.hpp"
#include										"Map.hpp"

PathFinding::PathFinding(std::unique_ptr<Map> &map) : _map(map) {

}

PathFinding::~PathFinding() {

}

std::shared_ptr<_SPoint>						PathFinding::getPoint(int x, int y) {
	for (std::vector<std::shared_ptr<_SPoint> >::iterator it = _openList.begin(); it != _openList.end(); ++it) {
		if ((*it)->x == x && (*it)->y == y) {
			//std::cout << "Point exist in openList" << std::endl;
			return (*it);
		}
	}

	for (std::vector<std::shared_ptr<_SPoint> >::iterator it = _closeList.begin(); it != _closeList.end(); ++it) {
		if ((*it)->x == x && (*it)->y == y) {
			//std::cout << "Point exist in closeList" << std::endl;
			return (*it);
		}
	}

	//std::cout << "new Point" << std::endl;
	return (std::shared_ptr<_SPoint>(new _SPoint(x, y)));
}

int												PathFinding::getGScore(const std::shared_ptr<_SPoint> &current, const std::shared_ptr<_SPoint> &point) {
	if (current->x == point->x || current->y == point->y) {
		return (current->g + 10);
	} else {
		return (current->g + 14);
	}
}

int												PathFinding::getHScore(const std::shared_ptr<_SPoint> &current, const std::shared_ptr<_SPoint> &point) {
	return ((abs(current->x - point->x) + abs(current->y - point->y)) * 10);
}

void											PathFinding::computeScores(std::shared_ptr<_SPoint> &current, const std::shared_ptr<_SPoint> &end){
	current->g = getGScore(current, current->parent);
	current->h = getHScore(current, end);
	current->f = current->g + current->h;
}

void											PathFinding::addAdjacentTile(const std::shared_ptr<_SPoint> &current, std::shared_ptr<_SPoint> &point, const std::shared_ptr<_SPoint> &end) {
	//std::cout << "POINT: " << point->opened << " and G: " << point->g << " and GScrore: " << getGScore(current, point) << std::endl;
	if (!point->closed) {
		if (point->opened && point->g >= getGScore(current, point)) {
			point->parent = current;
			computeScores(point, end);
		} else {
			_openList.push_back(point);
			point->opened = true;
			point->parent = current;
			computeScores(point, end);
		}
	}
}

std::vector<std::pair<int, int> >				PathFinding::aStar(int x1, int y1, int x2, int y2) {
	std::vector<std::pair<int, int> >			path;
	std::shared_ptr<_SPoint>					start(new _SPoint(x1, y1));
	std::shared_ptr<_SPoint>					end(new _SPoint(x2, y2));
	std::shared_ptr<_SPoint>					current(new _SPoint(x1, y1));

	_closeList.emplace_back(start);
	start->closed = true;

	current->parent = start;
	computeScores(current, end);
	int n = 0;
	while ((current->x != end->x || current->y != end->y) && n < 100000) {

		// add adjacents valid tiles in openList
		if (current->y > 0 && _map->getTile(current->x, current->y - 1)->isPassable()) {
			addAdjacentTile(current, getPoint(current->x, current->y - 1), end);
		}
		if (current->x < _map->getWidth() - 1 && _map->getTile(current->x + 1, current->y)->isPassable()) {
			addAdjacentTile(current, getPoint(current->x + 1, current->y), end);
		}
		if (current->y < _map->getHeight() - 1 && _map->getTile(current->x, current->y + 1)->isPassable()) {
			addAdjacentTile(current, getPoint(current->x, current->y + 1), end);
		}
		if (current->x > 0 && _map->getTile(current->x - 1, current->y)->isPassable()) {
			addAdjacentTile(current, getPoint(current->x - 1, current->y), end);
		}

		/*std::cout << "X-> " << current->x << "  Y-> " << current->y << std::endl;
		std::cout << "and current g: " << current->g << std::endl;
		std::cout << "and current h: " << current->h << std::endl;
		std::cout << "and current f: " << current->f << std::endl << std::endl;

		std::cout << std::endl << "_openList: " << _openList.size() << std::endl;
		for (std::vector<std::shared_ptr<_SPoint> >::iterator it = _openList.begin(); it != _openList.end(); ++it) {
			std::cout << "X-> " << (*it)->x << "  Y-> " << (*it)->y << std::endl;
			std::cout << "g: " << (*it)->g << std::endl;
			std::cout << "h: " << (*it)->h << std::endl;
			std::cout << "f: " << (*it)->f << std::endl;
		}
		std::cout << std::endl << "_closeList: " << _closeList.size() << std::endl;
		for (std::vector<std::shared_ptr<_SPoint> >::iterator it = _closeList.begin(); it != _closeList.end(); ++it) {
			std::cout << "X-> " << (*it)->x << "  Y-> " << (*it)->y << std::endl;
		}
		std::cout << std::endl << std::endl;*/

		// find best tile in openList
		bool hasToGoBack = true;
		for (std::vector<std::shared_ptr<_SPoint> >::iterator it = _openList.begin(); it != _openList.end(); ++it) {
			if ((*it)->f <= current->f) {
				// go on next closer tile
				current = *it;

				_openList.erase(it);
				current->opened = false;

				_closeList.emplace_back(current);
				current->closed = true;

				hasToGoBack = false;

				break;
			}
		}
		if (hasToGoBack) {
			if (_openList.size() > 0) {
				// go on next closer tile
				current = *(_openList.end() - 1);

				_openList.erase((_openList.end() - 1));
				current->opened = false;

				_closeList.emplace_back(current);
				current->closed = true;
			}
		}

		//std::cout << n << std::endl;

		++n;
	}

	_openList.clear();
	_closeList.clear();
	for (std::vector<std::shared_ptr<_SPoint> >::iterator it = _openList.begin(); it != _openList.end(); ++it) {
		(*it)->opened = false;
	}
	for (std::vector<std::shared_ptr<_SPoint> >::iterator it = _closeList.begin(); it != _closeList.end(); ++it) {
		(*it)->closed = false;
	}

	while (current->parent != nullptr && (current->x != start->x || current->y != start->y)) {
		path.emplace_back(std::pair<int, int>(current->x, current->y));
		current = current->parent;
	}

	return (path);
}