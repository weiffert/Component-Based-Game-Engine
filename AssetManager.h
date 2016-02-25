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

	//Adds the proper data.
	void add(sf::Image*); 
	void add(sf::Sound*); 
	void add(sf::Texture*);

private:
	std::vector<sf::Image*> image;
	std::vector<sf::Sound*> sound;
	std::vector<sf::Texture*> texture;

};
