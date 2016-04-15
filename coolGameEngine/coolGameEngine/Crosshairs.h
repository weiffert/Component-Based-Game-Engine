#pragma once
#include "SystemManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

class Crosshairs
{
public:
	Crosshairs();
	Crosshairs(SystemManager *);
	~Crosshairs();
	void control(sf::RenderWindow *, SystemManager *);
	void loadTexture(std::string, SystemManager *);
private:
	sf::Sprite* crosshair;
	sf::Texture file;
};
