/**
* moz
*/

#include								"AIv1.hpp"
#include								"PersonSpirit.hpp"
#include								"Map.hpp"
#include								"Tile.hpp"
#include								"APrimaryItem.hpp"
#include								"PathFinding.hpp"

AIv1::AIv1(std::unique_ptr<Map> &map) : _map(map) {
}

AIv1::~AIv1() {
}

// RETURN LA CASE LA PLUS PROCHE DU PERSON AUTOUR DE LA DESTINATION ET ACCESSIBLE
// PAS LA CASE ELLE-MEME !!!

std::pair<int, int>						AIv1::getTargetTile(const std::vector<std::shared_ptr<Tile> > &mapViewFieldPtr, const PersonSpirit &person) {
	//std::vector<std::pair<int, float> >	weights;
	std::pair<int, int>					targetCoord;
	float								weight = -1;
	float								newWeight;
	std::shared_ptr<Tile>				targetTile;
	std::vector<APrimaryItem>			primaryItems;
	int									potentialWater = 0;
	int									potentialFood = 0;
	int									potentialMissingWater = 0;
	int									potentialMissingFood = 0;

	//std::cout << "TYPE:" << std::endl;
	targetTile = *(mapViewFieldPtr.begin());
	for (std::vector<std::shared_ptr<Tile> >::const_iterator it = mapViewFieldPtr.begin(); it != mapViewFieldPtr.end(); ++it) {
		std::cout << _map->distance(person.getId(), (*it)->getId()) << std::endl;

		primaryItems = (*it)->getPrimaryItems();
		for (std::vector<APrimaryItem>::iterator piIt = primaryItems.begin(); piIt != primaryItems.end(); ++piIt) {
			// si water
			potentialMissingWater += piIt->getQuantity();
			// si food
			potentialMissingFood += piIt->getQuantity();
		}
		potentialMissingWater = 100 - (potentialWater + person.getThirst());
		potentialMissingFood = 100 - (potentialFood + person.getHunger());

		newWeight = _map->distance(person.getId(), (*it)->getId()) +
			((potentialMissingWater > 100 ? 100 : potentialMissingWater) / 2) +
			((potentialMissingFood > 100 ? 100 : potentialMissingFood) / 1.5);

		if (weight < 0 || newWeight < weight) {
			weight = newWeight;
			targetTile = *it;
		}

		//weights.emplace_back((*it)->getId(), weight);
	}

	targetCoord = _map->convertSmpDimToDblDim(targetTile->getId());
	PathFinding *pf = new PathFinding(_map);
	std::vector<std::pair<int, int> >	path;
	path = pf->aStar(0, 0, targetCoord.first, targetCoord.second);
	for (std::vector<std::pair<int, int> >::iterator it = path.end() - 1; it != path.begin() - 1; --it) {
		//std::cout << "X: " << it->first << " Y: " << it->second << std::endl;
		(_map->getTile(it->first, it->second)->getSprite())->setColor(sf::Color::Red);
	}

	// first tile in the path
	if (path.size() > 0) {
		return (*(path.end() - 1));
	} else {
		return (std::pair<int, int>(person.getX(), person.getY()));
	}
}