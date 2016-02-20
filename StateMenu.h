#pragma once
#include "BaseState.h"
#include "SystemManager.h"
class StateMenu :
	public BaseState
{
private:

	SystemManager* systemManager;

public:
	StateMenu(SystemManager *);
	~StateMenu();

	int menuUpdate(double);
	void render(double, sf::RenderWindow);

};

