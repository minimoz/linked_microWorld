/**
* moz
*/

#ifndef															RESOURCEMANAGER_HPP__
# define														RESOURCEMANAGER_HPP__

# include														<iostream>
# include														<vector>
# include														<memory>

# include														<SFML/Graphics.hpp>

# define														PATH_IMAGES_ "images/"

class ResourceManager {

private:
	ResourceManager();
	ResourceManager(const ResourceManager&) {};
	~ResourceManager();

	ResourceManager&											operator=(const ResourceManager&) {};

	static ResourceManager										*_instance;
	std::vector<std::pair<std::string, sf::Texture *> >			_textures;

public:
	static ResourceManager										*getInstance();
	const std::vector<std::pair<std::string, sf::Texture *> >&	getTextures();
	const sf::Texture											*getTexture(const std::string&);
	int															addTexture(const std::string&);
	//void	setTextures(std::vector<std::shared_ptr<std::pair<std::string, sf::Texture> > > textures);

};

#endif															/* RESOURCEMANAGER_HPP__ */
