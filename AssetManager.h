#pragma once
#include <string>
#include <vector>
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

class AssetManager : public BaseState
{
private:
	std::vector<sf::Image*> image; //hold images in a vector for each state in another vector.
	std::vector<sf::Sound*> sound; //hold sounds in a vector for each state in another vector.
	std::vector<sf::Texture*> texture; //hold textures in a vector for each state in another vector.

public:
	AssetManager();
	~AssetManager(); //Destructor. Deletes the images and sounds.
	sf::Image* getImage(int); //Returns an image for a property.
	sf::Sound* getSound(int); //Returns a sound for a property.
	sf::Texture* getTexture(int); //Returns a texture for a property.
	void addImage(sf::Image*); //Adds an image to the vector.
	void addSound(sf::Sound*); //Adds a sound to the vector.
	void addTexture(sf::Texture*); //Adds a texture to the vector.
};
