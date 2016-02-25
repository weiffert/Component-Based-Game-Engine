#pragma once
#include <string>
#include <vector>
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include "BaseState.h"

class AssetManager : public BaseState
{
public:
	AssetManager();
	//Destructor. Deletes the images and sounds.
	~AssetManager(); 

	//Return the proper data.
	sf::Image* getImage(int);
	sf::Image* getImage(std::string);
	sf::Sound* getSound(int);
	sf::Sound* getSound(std::string);
	sf::Texture* getTexture(int);
	sf::Texture* getTexture(std::string);

	//Adds the proper data.
	void add(sf::Image*); 
	void add(sf::Sound*); 
	void add(sf::Texture*);
	void addImageString(std::string);
	void addSoundString(std::string);
	void addTextureString(std::string);

private:
	//Holds the data.
	std::vector<sf::Image*> image;
	std::vector<sf::Sound*> sound;
	std::vector<sf::Texture*> texture;
	//Holds strings in the same position as the data.
	std::vector<std::string> imageNames;
	std::vector<std::string> soundNames;
	std::vector<std::string> textureNames;

};
