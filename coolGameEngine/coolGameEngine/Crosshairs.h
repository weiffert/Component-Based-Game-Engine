#pragma once
#include "SystemManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

class Crosshairs
{
public:
	Crosshairs();
	~Crosshairs();
	void control(sf::RenderWindow *, SystemManager *);
	void loadTexture(std::string);
private:
	sf::Sprite crosshair;
	sf::Texture file;
};
