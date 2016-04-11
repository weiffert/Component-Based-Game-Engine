#include "MissileLauncher.h"

#include <iostream>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "MissileExploder.h"
#include "SystemManager.h"
#include "Property.h"
#include "Entity.h"


MissileLauncher::MissileLauncher()
{
}


MissileLauncher::~MissileLauncher()
{
}


//Fires a missile
int MissileLauncher::fire(Entity *currentMissile, Entity *currentBase, sf::RenderWindow *window, SystemManager *systemManager)
{
	if (currentBase->hasComponent("CurrentMissileCount"))
	{
		//Shoots missile if it has missiles left
		int missileCount = currentBase->getComponent("CurrentMissileCount")->getDataInt().at(0);
		if (missileCount > 0)
		{
			//Delete data for exploding position and starting position for missile
			if (currentMissile->hasComponent("StartingPosition"))
				currentMissile->getComponent("StartingPosition")->deleteData();
			if (currentMissile->hasComponent("ExplodingPosition"))
				currentMissile->getComponent("ExplodingPosition")->deleteData();

			//Push back new values with starting and ending positions
			if (currentMissile->hasComponent("StartingPosition") && currentBase->hasComponent("CurrentPosition"))
			{
				std::vector<double> startPosition = currentBase->getComponent("CurrentPosition")->getDataDouble();
				currentMissile->getComponent("StartingPosition")->addData(startPosition.at(0)); //x for Base1
				currentMissile->getComponent("StartingPosition")->addData(startPosition.at(1)); //y for Base1
				currentMissile->getComponent("ChemTrail")->deleteData();
				currentMissile->getComponent("ChemTrail")->addData(startPosition.at(0));
				currentMissile->getComponent("ChemTrail")->addData(startPosition.at(1));
			}

			//Set current position to above values
			if (currentMissile->hasComponent("ExplodingPosition"))
			{
				std::cout << sf::Mouse::getPosition(*window).x << "x\ny " << sf::Mouse::getPosition(*window).y << std::endl;
				currentMissile->getComponent("ExplodingPosition")->addData(sf::Mouse::getPosition(*window).x);
				currentMissile->getComponent("ExplodingPosition")->addData(sf::Mouse::getPosition(*window).y);
			}

			//Sets slope (Which is x/y)
			if (currentMissile->hasComponent("Slope"))
				currentMissile->getComponent("Slope")->deleteData();

			double changeX = 0;
			if (currentMissile->hasComponent("ExplodingPosition") && currentMissile->hasComponent("StartingPosition"))
				changeX = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0) - currentMissile->getComponent("StartingPosition")->getDataDouble().at(0);

			double changeY = 0;
			if (currentMissile->hasComponent("ExplodingPosition") && currentMissile->hasComponent("StartingPosition"))
				changeY = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1) - currentMissile->getComponent("StartingPosition")->getDataDouble().at(1);

			if (currentMissile->hasComponent("Slope"))
			{
				currentMissile->getComponent("Slope")->deleteData();
				currentMissile->getComponent("Slope")->addData(setSlope(changeX, changeY));
			}

			if (currentMissile->hasComponent("Fired"))
			{
				currentMissile->getComponent("Fired")->deleteData();
				currentMissile->getComponent("Fired")->addData(true);
			}

			//Decrease missiles left
			currentBase->getComponent("CurrentMissileCount")->deleteData();
			currentBase->getComponent("CurrentMissileCount")->addData(--missileCount);
			return 1;
		}
	}

	//If it doesn't, do not fire and possibly tell the user
	return 0;
}


//Sets the amount of missiles left in the missile launcher to an int 
void MissileLauncher::setMissilesLeft(int a)
{
  missilesLeft = a;
}


//Sets the amount of missiles left in the missile launcher to an int 
void MissileLauncher::setTotalMissiles(int a)
{
  totalMissiles = a;
}


double MissileLauncher::setSlope(double pathX, double pathY)
{
  double speedX;
  
  speedX =pathX / pathY;
  
  return speedX;
}


int MissileLauncher::getMissilesLeft()
{
  return missilesLeft;
}


int MissileLauncher::getTotalMissiles()
{
  return totalMissiles;
}


void MissileLauncher::update(sf::RenderWindow *window, Entity *Base1, Entity *Base2, Entity *Base3)
{
	double slope;
	double temp1, temp2;
	std::vector<Entity*> bases;
	bases.push_back(Base1);
	bases.push_back(Base2);
	bases.push_back(Base3);

	//Goes through all the missiles for the three bases
	for (int base = 0; base < 3; base++)
	{
		std::vector<Entity *> missiles = bases.at(base)->getComponent("MissilesHeld")->getDataEntity();
		for (int i = 0; i < 10; i++)
		{
			if (missiles.at(i)->getComponent("Fired")->getDataBool().at(0))
			{
				if (missiles.at(i)->hasComponent("Slope"))
					slope = missiles.at(i)->getComponent("Slope")->getDataDouble().at(0);
				if (missiles.at(i)->hasComponent("CurrentPosition"))
				{
					temp1 = missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) + slope;
					missiles.at(i)->getComponent("CurrentPosition")->deleteData();
					missiles.at(i)->getComponent("CurrentPosition")->addData(temp1);
					temp1 = missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) - 1;
					missiles.at(i)->getComponent("CurrentPosition")->deleteData();
					missiles.at(i)->getComponent("CurrentPosition")->addData(temp1);
				}
				if (missiles.at(i)->hasComponent("Sprite"))
					missiles.at(i)->getComponent("Sprite")->getDataSprite().at(0)->move(slope, -1);
				
				//Adjust Chem Trail

				if (missiles.at(i)->hasComponent("ChemTrail"))
				{
					temp1 = missiles.at(i)->getComponent("ChemTrail")->getDataInt().at(0);
					temp2 = missiles.at(i)->getComponent("ChemTrail")->getDataInt().at(1);
					missiles.at(i)->getComponent("ChemTrail")->deleteData();
					missiles.at(i)->getComponent("ChemTrail")->addData(temp1);
					missiles.at(i)->getComponent("ChemTrail")->addData(temp2);
					missiles.at(i)->getComponent("ChemTrail")->addData(missiles.at(i)->
						getComponent("CurrentPosition")->getDataDouble().at(0));
					if (missiles.at(i)->hasComponent("CurrentPosition"))
						missiles.at(i)->getComponent("ChemTrail")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));
				}
				
				
				//If the current Missile is positioned on its explosion point, (give an error of .1)

				//Check x values
				if (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) - .1 <=
					missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) &&
					missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) + .1 >=
					missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0))
				{
					//check y values
					if (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) - .1 <=
						missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) &&
						missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) + .1 >=
						missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1))
					{
						//Make the missile explode
						MissileExploder exploder;
						exploder.control(window, missiles.at(i));
						missiles.at(i)->getComponent("Life")->deleteData();
						missiles.at(i)->getComponent("Life")->addData(false);
					}
				}
			}
		}
	}
}
