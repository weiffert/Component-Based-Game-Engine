#pragma once
//includes
#include "BaseState.h"
#include <string>

class Game
{
public:
	Game(int, int, std::string);
	~Game();
	int run();
	
private:
	int gameLoop();
	void changeState(BaseState*);
	void changeState(BaseState*, int);
	void changeState(BaseState*, std::string);

protected:
	bool isRunning;
	int exitCode;
	std::string gameName;
	sf::Vector2i windowResolution;
	BaseState* state;
	BaseState* stateLast;
	SystemManager* systemManager;

	sf::RenderWindow gameWindow{ sf::VideoMode(windowResolution.x, windowResolution.y), gameName };
};
