#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateWelcome :
	public BaseState
{
public:
	//Takes in Game's systemManager and assetManager.
	StateWelcome(SystemManager *, AssetManager *);
	~StateWelcome();

	//Update function. Overloads the pure virtual update function in BaseState.
	void update(double, sf::RenderWindow *);

private:
	//This should be in BaseState.
	SystemManager* systemManager;

};

