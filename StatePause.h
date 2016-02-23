#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StatePause :
	public BaseState
{
private:

	SystemManager* systemManager;

public:
	StatePause(SystemManager *, AssetManager *);
	~StatePause();
	void update(double, sf::RenderWindow*);
};

