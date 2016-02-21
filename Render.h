#pragma once
#include <vector>
#include <string>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "BaseController.h"
#include "Entity.h"

class Render :
	public BaseController
{
public:
	Render();
	~Render();
	void control(sf::RenderWindow *, Entity *);
};

