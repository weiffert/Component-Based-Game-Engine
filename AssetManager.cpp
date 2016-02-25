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


//Takes in the location in the vector.
//Returns an image for a property.
sf::Image* AssetManager::getImage(int location)
{
	if (location < image.size() && location >= 0)
	{
		return image.at(location);
	}

	return nullptr;
}


//Takes in the filename.
//Returns an image for a property.
sf::Image* AssetManager::getImage(std::string filename)
{
	if (filename)
	{
		return image.at(location);
	}

	return nullptr;
}


//Takes in the location in the vector.
//Returns a sound for a property.
sf::Sound* AssetManager::getSound(int location)
{
	if (location < sound.size() && location >= 0)
	{
		return sound.at(location);
	}

	return nullptr;
}


//Takes in the location in the vector.
//Returns a sound for a property.
sf::Sound* AssetManager::getSound(std::string)
{
	if (location < sound.size() && location >= 0)
	{
		return sound.at(location);
	}

	return nullptr;
}


//Takes in the location in the vector.
//Returns a texture for a property.
sf::Texture* AssetManager::getTexture(int location)
{
	if (location < texture.size() && location >= 0)
	{
		return texture.at(location);
	}

	return nullptr;
}


//Adds an image to the vector for the state.
//Takes in a image.
void AssetManager::add(sf::Image* newImage)
{
	image.push_back(newImage);
}


//Adds a sound to the vector for the state.
//Takes in a sound.
void AssetManager::add(sf::Sound* newSound)
{
	sound.push_back(newSound);
}


//Adds an image to the vector for the state.
//Takes in a texture.
void AssetManager::add(sf::Texture* newTexture) 
{
	texture.push_back(newTexture);
}