#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"

class Plane
{
private:
	int missilesLeft, totalMissiles, targetOne, targetTwo, targetThree;
	SystemManager *systemManager;
	AssetManager *assetManager;
public:
	Plane();
	Plane(SystemManager *, AssetManager *);
	Plane(int, int, int, SystemManager *, AssetManager *);
	~Plane();
	double setSlope(double, double);
	int launchMissiles(sf::RenderWindow *); //Returns 0 if it fails to launch, 1 if it successfully launches
	void update(sf::RenderWindow *);
	void launchPlane(sf::RenderWindow *, int);
};
