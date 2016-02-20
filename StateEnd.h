#pragma once
#include "BaseState.h"
#include "SystemManager.h"

class StateEnd :
	public BaseState
{
private:

	SystemManager* systemManager;

public:
	StateEnd(SystemManager *);
	~StateEnd();
	int endUpdate(double);
	void render(double, sf::RenderWindow);
};

