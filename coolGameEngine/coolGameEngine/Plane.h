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
	void setTargets(bool[6]); //Takes an array of bools respresenting which cities are alive
	double setSlope(double, double);
	void setTotalMissiles(int);
	void setMissilesLeft(int);
	int getMissilesLeft();
	int getTotalMissiles();
	int launchMissiles(sf::RenderWindow *, SystemManager *); //Returns 0 if it fails to launch, 1 if it successfully launches
	void update(sf::RenderWindow *, SystemManager *);
	void launchPlane(sf::RenderWindow *, SystemManager*, int);
	bool intersection(Entity *, sf::CircleShape *, sf::Sprite *);
	bool pointIntersection(sf::CircleShape, sf::Vector2f);
	int launchMissiles(sf::RenderWindow *); //Returns 0 if it fails to launch, 1 if it successfully launches
	void update(sf::RenderWindow *);
	void launchPlane(sf::RenderWindow *, int);
};
