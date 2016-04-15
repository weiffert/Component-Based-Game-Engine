#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateStatic : 
	public BaseState
{
public:
	StateStatic();
	//Takes in Game's systemManager and assetManager.
	StateStatic(SystemManager *, AssetManager *);
	~StateStatic();

	//Update function. Overloads the pure virtual update function in BaseState.
	virtual std::string update(double, sf::RenderWindow *);
};