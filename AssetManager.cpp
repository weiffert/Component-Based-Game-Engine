#include "stdafx.h"
#include "AssetManager.h"
#include "BaseState.h"
#include <string>
#include <vector>
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{

}

sf::Image* AssetManager::getImage(int location) //Returns an image for a property.
{
	return image.at(location);
}

sf::Sound* AssetManager::getSound(int location) //Returns a sound for a property.
{
	return sound.at(location);
}

sf::Texture* AssetManager::getTexture(int location) //Returns a texture for a property.
{
	return texture.at(location);
}

void AssetManager::addImage(sf::Image* newImage) //Adds an image to the vector for the state.
{
	image.push_back(newImage);
}

void AssetManager::addSound(sf::Sound* newSound) //Adds a sound to the vector for the state.
{
	sound.push_back(newSound);
}

void AssetManager::addTexture(sf::Texture* newTexture) //Adds an image to the vector for the state.
{
	texture.push_back(newTexture);
}