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
	void initializeManagers();
	int gameLoop();
	bool isRunning();
	void changeState(BaseState*);
	void changeState(BaseState*, int);
	void changeState(BaseState, std::string);
};
