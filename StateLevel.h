#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateLevel :
	public BaseState
{
public:
	//Takes in Game's systemManager and assetManager.
	StateLevel(SystemManager*, AssetManager *);
	~StateLevel();

	//Update function. Overloads the pure virtual update function in BaseState.
	void update(double, sf::RenderWindow*);

private:
	//This should be in BaseState.
	SystemManager* systemManager;
};

