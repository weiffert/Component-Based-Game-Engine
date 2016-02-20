#pragma once
#include "BaseState.h"
#include "SystemManager.h"

class StatePause :
	public BaseState
{
private:

	SystemManager* systemManager;

public:
	StatePause(SystemManager *);
	~StatePause();

	int pauseUpdate(double);
	void render(double, sf::RenderWindow)
};

