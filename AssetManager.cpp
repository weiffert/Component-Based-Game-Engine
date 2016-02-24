#include "stdafx.h"
#include <string>
#include <vector>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "AssetManager.h"


AssetManager::AssetManager()
{

}


AssetManager::~AssetManager()
{

}


sf::Image* AssetManager::getImage(int location) //Returns an image for a property.
{
	if (location < image.size() && location >= 0)
	{
		return image.at(location);
	}

	return nullptr;
}


sf::Sound* AssetManager::getSound(int location) //Returns a sound for a property.
{
	if (location < sound.size() && location >= 0)
	{
		return sound.at(location);
	}

	return nullptr;
}


sf::Texture* AssetManager::getTexture(int location) //Returns a texture for a property.
{
	if (location < texture.size() && location >= 0)
	{
		return texture.at(location);
	}

	return nullptr;
}


void AssetManager::add(sf::Image* newImage) //Adds an image to the vector for the state.
{
	image.push_back(newImage);
}


void AssetManager::add(sf::Sound* newSound) //Adds a sound to the vector for the state.
{
	sound.push_back(newSound);
}


void AssetManager::add(sf::Texture* newTexture) //Adds an image to the vector for the state.
{
	texture.push_back(newTexture);
}