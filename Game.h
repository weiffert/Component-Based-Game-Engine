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
	std::string gameName;
	sf::vector2i windowResolution;
	bool isRunning;
	int exitCode;
	*BaseState state;
	*SystemManager systemManager;
	int gameLoop();
	void changeState(BaseState*);
	void changeState(BaseState*, int);
	void changeState(BaseState, std::string);
};
