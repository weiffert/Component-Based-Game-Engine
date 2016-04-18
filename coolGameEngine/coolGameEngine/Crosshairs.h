#pragma once
#include "SystemManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

class Crosshairs
{
public:
	Crosshairs();
	~Crosshairs();
	void fitSize(SystemManager *, int); //Gives the crosshairs a new size
	void control(sf::RenderWindow *, SystemManager *);
private:
	sf::Sprite* crosshair = nullptr;
	sf::Texture file;
};
