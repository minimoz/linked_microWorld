/**
* moz
*/

#ifndef															RESOURCEMANAGER_HPP__
# define														RESOURCEMANAGER_HPP__

# include														<iostream>
# include														<vector>
# include														<memory>

# include														<SFML/Graphics.hpp>

# define														PATH_IMAGES_	"images/"
# define														FONT_PATH_		"fonts/"

class ResourceManager {

private:
	ResourceManager();
	ResourceManager(const ResourceManager&) {};
	~ResourceManager();

	ResourceManager&											operator=(const ResourceManager&) {};

	static ResourceManager										*_instance;
	std::vector<std::pair<std::string, sf::Texture *> >			_textures;
	std::vector<std::pair<std::string, sf::Font *> >			_fonts;

public:
	static ResourceManager										*getInstance();
	const std::vector<std::pair<std::string, sf::Texture *> >&	getTextures();
	const std::vector<std::pair<std::string, sf::Font *> >&		getFonts();

	const sf::Texture											*getTexture(const std::string&);
	const sf::Font												*getFont(const std::string&);
};

#endif															/* RESOURCEMANAGER_HPP__ */
