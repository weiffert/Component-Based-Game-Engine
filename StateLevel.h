#pragma once
#include "BaseState.h"
#include "SystemManager.h"

class StateLevel :
	public BaseState
{
private:

	SystemManager* systemManager;

public:
	StateLevel(SystemManager*);
	~StateLevel();
	void update(double, sf::RenderWindow);
	void render(double, sf::RenderWindow);
};

