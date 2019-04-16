#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceManager.hpp"

class AudioManager : public ResourceManager<AudioManager, sf::SoundBuffer> {
public:
	AudioManager() : ResourceManager("audio.cfg") {}

	/*bool Load(sf::SoundBuffer* l_resource, const std::string& l_path)
	{
		return l_resource->loadFromFile(Utils::GetWorkingDirectory() + l_path);
	}*/
};

#endif