#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <SFML/Graphics/Font.hpp>
#include "ResourceManager.hpp"

class FontManager : public ResourceManager<FontManager, sf::Font> {
public:
	FontManager() : ResourceManager("fonts.cfg") {}

	//bool Load(sf::Font* l_resource, const std::string& l_path) 
	//{
	//	return l_resource->loadFromFile(Utils::GetWorkingDirectory() + l_path);
	//}
};

#endif