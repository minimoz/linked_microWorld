/**
 * moz
 */

#include													"PersonBody.hpp"
#include													"ResourceManager.hpp"
#include													"Tile.hpp"
#include													"Map.hpp"

//PersonBody::PersonBody() : PersonSpirit() {
//	_x = 0;
//	_y = 0;
//	_viewField = 2;
//	_sex = Male;
//	_age = 0;
//	_hunger = 100;
//	_thirst = 100;
//}

PersonBody::PersonBody(std::unique_ptr<Map> &map, int id) : PersonSpirit(map, id) {
	_x = 0;
	_targetX = 0;
	_y = 0;
	_targetY = 0;
	_viewField = 2;
	_sex = Male;
	_age = 0;
	_hunger = 100;
	_thirst = 100;
}

PersonBody::~PersonBody() {
	// delete
}

void														PersonBody::toString() {
	std::cout << "Person #" << _id << std::endl
		<< "   |- age: " << _age << std::endl
		<< "   |- sex: " << _sex << std::endl
		<< "   |- hunger: " << _hunger << std::endl
		<< "   |- thirst: " << _thirst << std::endl << std::endl;
}

const int													PersonBody::getX() const {
	return (_x);
}

int															PersonBody::getTargetX() {
	return (_targetX);
}

const int													PersonBody::getY() const {
	return (_y);
}

int															PersonBody::getTargetY() {
	return (_targetY);
}

int															PersonBody::getViewField() {
	return (_viewField);
}

const Sex													&PersonBody::getSex() {
	return (_sex);
}

int															PersonBody::getAge() {
	return (_age);
}

int															PersonBody::getAgeInYear() {
	return (_age / 365.25);
}

const int													PersonBody::getHunger() const {
	return (_hunger);
}

const int													PersonBody::getThirst() const {
	return (_thirst);
}

void														PersonBody::init() {
	_sprite.setTexture(*ResourceManager::getInstance()->getTexture(PATH_IMAGES_ "person.png"));
}

void														PersonBody::initPos() {
	std::pair<int, int>										coord = PersonSpirit::getRandomValidPos();

	_targetX = coord.first;
	_targetY = coord.second;
}

void														PersonBody::update(int mapWidth, int mapHeight) {
	live();
	move();

	//std::cout << PersonSpirit::getId() << " -> X: " << _x << " Y: " << _y << std::endl;

	_sprite.setPosition(_x * TILE_SIZE_, _y * TILE_SIZE_);
}

/**
* hunger is reduce by 1 if random 0-100 is higher than HUNGER_RATE_ (90)
* means that there is 90% chance that Person lost 1 hunger
*
* same for thirst but lost 5 thirst (we die faster from thirst than hunger)
*/
void														PersonBody::live() {
	++_age;
	_hunger -= (PersonSpirit::getRandomNb(0, 100)) > HUNGER_RATE_ ? 0 : HUNGER_COEFF_;
	_thirst -= (PersonSpirit::getRandomNb(0, 100)) > THIRST_RATE_ ? 0 : THIRST_COEFF_;
}

void														PersonBody::move() {
	std::pair<int, int>										dest;

	/*std::cout << "ViewField => ";
	for (std::vector<std::shared_ptr<Tile> >::iterator it = mapViewFieldPtr->begin(); it != mapViewFieldPtr->end(); ++it) {
		(*it)->toString();
	}*/

	_x = _targetX;
	_y = _targetY;

	dest = PersonSpirit::getDest(_x, _y, _viewField);
	//std::cout << "DEST_X: " << dest.first << " DEST_Y: " << dest.second << std::endl;
	/*_targetX = dest.first;
	_targetY = dest.second;*/

	_targetX = PersonSpirit::getRandomNb(_x - 1, (_x == getMap()->getWidth() - 1 ? _x : _x + 2));
	_targetY = PersonSpirit::getRandomNb(_y - 1, (_y == getMap()->getHeight() - 1 ? _y : _y + 2));

}
