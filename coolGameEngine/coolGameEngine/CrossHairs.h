#pragma once
#include "SystemManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

class CrossHairs
{
public:
	CrossHairs();
	~CrossHairs();
	void control(sf::RenderWindow *, SystemManager *);
	void loadSprite(std::string);
private:
	sf::Sprite crossHair;
	sf::Texture file;
};
