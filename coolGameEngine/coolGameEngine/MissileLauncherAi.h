#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"

class MissileLauncherAi
{
private:
	int targetOne, targetTwo, targetThree;
	SystemManager *systemManager;
	AssetManager *assetManager;

public:
	MissileLauncherAi();
	MissileLauncherAi(AssetManager *, SystemManager *);
	~MissileLauncherAi();
	void setTargets(bool[6]); //Takes an array of bools respresenting which cities are alive
	int launchAmmount();
	double setSlope(double, double);
	int launchMissiles(Entity *, sf::RenderWindow *); //Returns 0 if it fails to launch, 1 if it successfully launches
	void update(sf::RenderWindow *, Entity *);

};
