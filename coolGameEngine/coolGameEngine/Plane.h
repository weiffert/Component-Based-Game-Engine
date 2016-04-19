#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "Entity.h"

class Plane
{
private:
	int missilesLeft, totalMissiles, targetOne, targetTwo, targetThree;

public:
	Plane();
	Plane(int, int, int, SystemManager *);
	~Plane();
	void setTargets(bool[6]); //Takes an array of bools respresenting which cities are alive
	double setSlope(int, int);
	void setTotalMissiles(int);
	void setMissilesLeft(int);
	int getMissilesLeft();
	int getTotalMissiles();
	int launchMissiles(Entity *, sf::RenderWindow *, SystemManager *); //Returns 0 if it fails to launch, 1 if it successfully launches
	void update(sf::RenderWindow *,  SystemManager *);
	void launchPlane(sf::RenderWindow *, SystemManager*, int);
};
