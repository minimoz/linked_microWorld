/**
 * moz
 */

#ifndef						PERSON_HPP__
# define					PERSON_HPP__

# include					<iostream>

# include					<SFML/Graphics.hpp>

# include					"AEntity.hpp"
# include					"ResourceManager.hpp"

class						Person : public AEntity {

private:
	int						_id;
	int						_x;
	int						_y;

public:
	Person();
	~Person();

	int						getX();
	int						getY();

	int						init();
	void					initPos(const int &, const int &);
	void					update(const int &, const int &);
	void					move();
};

#endif						/* PERSON_HPP__ */
