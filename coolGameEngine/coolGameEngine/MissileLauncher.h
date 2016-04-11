#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "Entity.h"

class MissileLauncher
{
public:
	MissileLauncher();
	~MissileLauncher();
	int fire(Entity *, Entity *, sf::RenderWindow *, SystemManager *);	//Returns 0 if it fails to launch, 1 if it successfully launches
	void setMissilesLeft(int);
	void setTotalMissiles(int);
	int getMissilesLeft();
	int getTotalMissiles();
	double setSlope(double, double);
	void update(sf::RenderWindow*, Entity *, Entity *, Entity *);
private:
	int missilesLeft;
	int totalMissiles;
};
