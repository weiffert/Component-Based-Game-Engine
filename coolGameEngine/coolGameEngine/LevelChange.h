#pragma once
#include "BaseController.h"

#include <string>
#include <iostream>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"

class LevelChange :
	public BaseController
{
public:
	LevelChange();
	~LevelChange();

	std::string control(SystemManager *, AssetManager *, sf::RenderWindow *);
};

