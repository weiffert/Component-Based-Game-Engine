#pragma once
//includes
#include "BaseState.h"
#include <string>

class Game
{
public:
	Game();
	~Game();
	int run();
private:
	bool isRunning;
	int exitCode;
	*BaseState state;
	*SystemManager systemManager;
	
	int gameLoop();
	void changeState(BaseState*);
	void changeState(BaseState*, int);
	void changeState(BaseState, std::string);
};
