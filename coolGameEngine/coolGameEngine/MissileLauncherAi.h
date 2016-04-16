#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "Entity.h"

class MissileLauncherAi
{
private:
	int missilesLeft, totalMissiles, targetOne, targetTwo, targetThree;
	SystemManager *systemManager;

public:
	MissileLauncherAi();
	MissileLauncherAi(SystemManager *, int, int);
	~MissileLauncherAi();
	void setTargets(bool[6]); //Takes an array of bools respresenting which cities are alive
	int launchAmmount();
	double setSlope(double, double);
	void setTotalMissiles(int);
	void setMissilesLeft(int);
	int getMissilesLeft();
	int getTotalMissiles();
	int launchMissiles(Entity *, sf::RenderWindow *); //Returns 0 if it fails to launch, 1 if it successfully launches
	void update(sf::RenderWindow *, Entity *);

};
