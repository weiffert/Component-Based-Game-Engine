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
	Game();
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
	sf::RenderWindow gameWindow;

	//The game loop
	int gameLoop();
};
