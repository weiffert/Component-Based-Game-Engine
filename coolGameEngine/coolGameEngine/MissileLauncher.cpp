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
			//if (currentMissile->hasComponent("StartingPosition"))
			//	currentMissile->getComponent("StartingPosition")->deleteData();

			if (currentMissile->hasComponent("ExplodingPosition"))
			{
				currentMissile->getComponent("ExplodingPosition")->deleteData();
				std::cout << sf::Mouse::getPosition(*window).x << "x\ny " << sf::Mouse::getPosition(*window).y << std::endl;
				currentMissile->getComponent("ExplodingPosition")->addData(sf::Mouse::getPosition(*window).x);
				currentMissile->getComponent("ExplodingPosition")->addData(sf::Mouse::getPosition(*window).y);
			}

			//Push back new values with starting and ending positions
			if (currentMissile->hasComponent("StartingPosition") && currentMissile->hasComponent("ChemTrail"))
			{
				currentMissile->getComponent("ChemTrail")->addData(currentMissile->getComponent("StartingPosition")->getDataDouble().at(0));
				currentMissile->getComponent("ChemTrail")->addData(currentMissile->getComponent("StartingPosition")->getDataDouble().at(1));
			}

			//Sets slope (Which is x/y)
			double changeX = 0;
			double changeY = 0;
			if (currentMissile->hasComponent("ExplodingPosition") && currentMissile->hasComponent("StartingPosition"))
			{
				changeX = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0) - currentMissile->getComponent("StartingPosition")->getDataDouble().at(0);
				changeY = -1 * currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1) - -1 * currentMissile->getComponent("StartingPosition")->getDataDouble().at(1);
			}

			if (currentMissile->hasComponent("Slope"))
			{
				currentMissile->getComponent("Slope")->deleteData();
				currentMissile->getComponent("Slope")->addData(changeY/changeX);
			}

			if (currentMissile->hasComponent("Fired"))
			{
				currentMissile->getComponent("Fired")->deleteData();
				currentMissile->getComponent("Fired")->addData(true);
			}

			//Decrease missiles left
			currentBase->getComponent("CurrentMissileCount")->deleteData();
			currentBase->getComponent("CurrentMissileCount")->addData(--missileCount);

			if (currentMissile->hasComponent("Move"))
			{
				currentMissile->getComponent("Move")->deleteData();
				currentMissile->getComponent("Move")->addData(true);
			}
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
	return pathY / pathX;
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
	sf::Vertex line[2];
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
				if (missiles.at(i)->hasComponent("CurrentPosition") && missiles.at(i)->hasComponent("StartingPosition") && missiles.at(i)->hasComponent("Velocity"))
				{
					double velocityX = missiles.at(i)->getComponent("Velocity")->getDataDouble().at(0);
					temp1 = missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) + velocityX;
					temp2 = slope * (temp1 - missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(0)) + -1 * missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(1);
					temp2 *= -1;

					missiles.at(i)->getComponent("Velocity")->deleteData();
					missiles.at(i)->getComponent("Velocity")->addData(velocityX);
					missiles.at(i)->getComponent("Velocity")->addData(temp2 - missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));

					missiles.at(i)->getComponent("CurrentPosition")->deleteData();
					missiles.at(i)->getComponent("CurrentPosition")->addData(temp1);
					missiles.at(i)->getComponent("CurrentPosition")->addData(temp2);


					sf::Sprite *s = missiles.at(i)->getComponent("Sprite")->getDataSprite().at(0);
					s->setPosition(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0), missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));
				}
				
				///Adjust Chem Trail if missile is still alive
				if (missiles.at(i)->getComponent("Life")->getDataBool() && missiles.at(i)->hasComponent("ChemTrail"))
				{
					line[0] = sf::Vertex(sf::Vector2f(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0)
						, missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1)));
					line[1] = sf::Vertex(sf::Vector2f(missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0)
						, missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1)));
					missiles.at(i)->getComponent("ChemTrail")->deleteData();
					missiles.at(i)->getComponent("ChemTrail")->addData(line);	
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
						bool notTrue = false;
						missiles.at(i)->getComponent("Life")->changeData(&notTrue, 0);
						missiles.at(i)->getComponent("Draw")->changeData(&notTrue, 0);
						missiles.at(i)->getComponent("Move")->changeData(&notTrue, 0);
					}
				}
			}
		}
	}
}
