/**
* moz
*/

#include																	"../headers/ResourceManager.hpp"

ResourceManager																*ResourceManager::_instance = 0;

ResourceManager::ResourceManager() {
	std::cout << "ResourceManager: Initialization..." << std::endl;
}

ResourceManager::~ResourceManager() {
	std::cout << "ResourceManager: Destruction." << std::endl;

	for (int i = 0; i < _textures.size(); ++i) {
		delete _textures[i].second;
		_textures.erase(_textures.begin() + i);
	}
}

ResourceManager																*ResourceManager::getInstance() {
	if (!_instance) {
		_instance = new ResourceManager();
	}
	return (_instance);
}

const std::vector<std::pair<std::string, sf::Texture *> >&					ResourceManager::getTextures() {
	return (_textures);
}

const std::vector<std::pair<std::string, sf::Font *> >&						ResourceManager::getFonts() {
	return (_fonts);
}

/**
* Check if the texture existe in the vector
* if yes, just return it
* if not, load it from the image file and return it
*/
const sf::Texture															*ResourceManager::getTexture(const std::string& imgName) {
	for (std::vector<std::pair<std::string, sf::Texture *> >::iterator it = _textures.begin(); it != _textures.end(); ++it) {
		if (it->first == imgName) {
			//std::cout << "DEBUG_MSG: using existing image." << std::endl;
			return (it->second);
		}
	}

	sf::Texture																*texture = new sf::Texture();
	if (texture->loadFromFile(imgName)) {
		_textures.push_back(std::pair<std::string, sf::Texture *>(imgName, texture));
		//std::cout << "DEBUG_MSG: loading image." << std::endl;
		return (_textures.back().second);
	}

	std::cout << "ERROR: image not found. Filled with an empty texture." << std::endl;
	_textures.push_back(std::pair<std::string, sf::Texture *>(imgName, new sf::Texture()));
	return (_textures.back().second);
}

const sf::Font																*ResourceManager::getFont(const std::string& fontName) {
	for (std::vector<std::pair<std::string, sf::Font *> >::iterator it = _fonts.begin(); it != _fonts.end(); ++it) {
		if (it->first == fontName) {
			//std::cout << "DEBUG_MSG: using existing font." << std::endl;
			return (it->second);
		}
	}

	sf::Font																*font = new sf::Font();
	if (font->loadFromFile(fontName)) {
		_fonts.push_back(std::pair<std::string, sf::Font *>(fontName, font));
		//std::cout << "DEBUG_MSG: loading image." << std::endl;
		return (_fonts.back().second);
	}

	std::cout << "ERROR: font not found. Filled with an empty font." << std::endl;
	_fonts.push_back(std::pair<std::string, sf::Font *>(fontName, new sf::Font()));
	return (_fonts.back().second);
}
