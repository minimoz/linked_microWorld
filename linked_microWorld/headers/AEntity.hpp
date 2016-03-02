/**
* moz
*/

#ifndef						AENTITY_HPP__
# define					AENTITY_HPP__

# include					<iostream>

# include					<SFML/Graphics.hpp>
# include					<memory>

# define					TILE_SIZE_ 16

//struct					s_color {
//	int						red;
//	int						green;
//	int						blue;
//	int						alpha;
//};

class AEntity {

protected:
	int						_id;
	sf::Sprite				_sprite;
	sf::Transform			_transform;
	std::string				_imgName;

public:
	AEntity();
	~AEntity();

	int						getId();
	sf::Sprite				*getSprite();
	const sf::Transform		&getTransform();
	const std::string		&getImgName();
	void					setSprite(const sf::Sprite &);
	void					setTransform(const sf::Transform &);
	void					setImgName(const std::string &);

	int						getRandomNb(int, int);
	void					draw(sf::RenderWindow *);

	virtual void			init() = 0;
};

#endif						/* AENTITY_HPP__ */
