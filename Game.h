#pragma once
#include <string>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class Game
{
public:
	Game(int, int, std::string);
	~Game();
	int run();
	
private:
	int gameLoop();

	int exitCode;
	std::string gameName;
	sf::Vector2i windowResolution;
	BaseState* state;
	SystemManager* systemManager;
	AssetManager* assetManager;

	sf::RenderWindow gameWindow{ sf::VideoMode(windowResolution.x, windowResolution.y), gameName };
};
