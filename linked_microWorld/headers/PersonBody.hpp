/**
 * moz
 */

#ifndef										PERSONBODY_HPP__
# define									PERSONBODY_HPP__

# include									<iostream>
# include									<memory>

# include									<SFML/Graphics.hpp>

# include									"PersonSpirit.hpp"

# define									HUNGER_RATE_	90
# define									HUNGER_COEFF_	1
# define									THIRST_RATE_	60
# define									THIRST_COEFF_	2

class PersonSpirit;
class ResourceManager;

enum										Sex {
	Male,
	Female,
	Other
};

class										PersonBody : public PersonSpirit {

private:
	int										_x;
	int										_targetX;
	int										_y;
	int										_targetY;
	int										_viewField;
	Sex										_sex;
	int										_age;
	int										_hunger;
	int										_thirst;

public:
	//PersonBody();
	PersonBody(std::unique_ptr<Map> &, int);
	~PersonBody();

	void									toString();

	const int								getX() const;
	int										getTargetX();
	const int								getY() const;
	int										getTargetY();
	int										getViewField();
	const Sex								&getSex();
	int										getAge();
	int										getAgeInYear();
	const int								getHunger() const;
	const int								getThirst() const;

	void									init();
	void									initPos();
	void									update(int, int);
	void									live();
	void									move();
};

#endif										/* PERSONBODY_HPP__ */
