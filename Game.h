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
	
	//Runs the game.
	int run();
	
private:
	int exitCode;
	std::string gameName;

	BaseState* state;
	SystemManager* systemManager;
	AssetManager* assetManager;

	sf::Vector2i windowResolution;
	sf::RenderWindow gameWindow{ sf::VideoMode(windowResolution.x, windowResolution.y), gameName };

	//The game loop
	int gameLoop();
};
