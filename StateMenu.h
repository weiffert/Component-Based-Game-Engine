#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateMenu :
	public BaseState
{
private:

	SystemManager* systemManger;

public:
	StateMenu(SystemManager *, AssetManager *);
	~StateMenu();
	void update(double, sf::RenderWindow *);
};

