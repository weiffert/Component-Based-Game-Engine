#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateWelcome :
	public BaseState
{
private:

	SystemManager* systemManager;

public:
	StateWelcome(SystemManager *, AssetManager *);
	~StateWelcome();
	int update(double, sf::RenderWindow *);
};

