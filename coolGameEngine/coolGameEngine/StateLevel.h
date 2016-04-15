#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateLevel :
	public BaseState
{
public:
	//Takes in Game's systemManager and assetManager.
	StateLevel();
	StateLevel(SystemManager*, AssetManager *);
	~StateLevel();

	//Update function. Overloads the pure virtual update function in BaseState.
	virtual std::string update(double, sf::RenderWindow*);
private:
	sf::Vector2i centerCoordinates;
};

