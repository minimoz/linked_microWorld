/**
* moz
*/

#ifndef						AENTITY_HPP__
# define					AENTITY_HPP__

# include					<iostream>

# include					<SFML/Graphics.hpp>

# define					TILE_SIZE_ 16

class AEntity {

protected:
	//sf::Texture			_texture;
	sf::Sprite				_sprite;
	sf::Transform			_transform;
	std::string				_imgName;

public:
	AEntity();
	~AEntity();

	//const sf::Texture&	getTexture();
	const sf::Sprite&		getSprite();
	const sf::Transform&	getTransform();
	const std::string&		getImgName();
	//void					setTexture(const sf::Texture &);
	void					setSprite(const sf::Sprite &);
	void					setTransform(const sf::Transform &);
	void					setImgName(const std::string &);

	int						getRandomNb(const int &, const int &);
	void					draw(sf::RenderWindow *);

	virtual int				init() = 0;
};

#endif						/* AENTITY_HPP__ */
