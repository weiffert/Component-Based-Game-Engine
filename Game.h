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
	bool isRunning;
	int exitCode;
	std::string gameName;
	sf::vector2i windowResolution;
	*BaseState state;
	*SystemManager systemManager;

	int gameLoop();
	void changeState(BaseState*);
	void changeState(BaseState*, int);
	void changeState(BaseState, std::string);
};
