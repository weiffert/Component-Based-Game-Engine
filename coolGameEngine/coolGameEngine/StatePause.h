#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StatePause :
	public BaseState
{
public:
	//Takes in Game's systemManager and assetManager.
	StatePause(SystemManager *, AssetManager *);
	~StatePause();

	//Update function. Overloads the pure virtual update function in BaseState.
	void update(double, sf::RenderWindow*);
};

