#include "MissileLauncher.h"

#include <iostream>
#include <math.h>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "MissileExploder.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Property.h"
#include "Entity.h"


MissileLauncher::MissileLauncher()
{
}


MissileLauncher::~MissileLauncher()
{
}


//Fires a missile
int MissileLauncher::fire(Entity *currentMissile, Entity *currentBase, sf::RenderWindow *window, SystemManager *systemManager, AssetManager *assetManager)
{
	if (currentMissile->hasComponent("Sprite") && currentMissile->hasComponent("Draw") && currentMissile->hasComponent("Fired"))
	{
		if (currentMissile->getComponent("Draw")->getDataBool().at(0) && !currentMissile->getComponent("Fired")->getDataBool().at(0))
		{
			sf::Sprite *s = currentMissile->getComponent("Sprite")->getDataSprite().at(0);
			sf::Texture *t = new sf::Texture;
			if (!t->loadFromFile("missile-transit.png"))
				std::cout << "Failed to open missile-transit.png" << std::endl;
			s->setTexture(*t, true);

			assetManager->add(t);
		}
	}

	if (currentBase->hasComponent("CurrentMissileCount"))
	{
		//Shoots missile if it has missiles left
		int missileCount = currentBase->getComponent("CurrentMissileCount")->getDataInt().at(0);
		if (missileCount > 0)
		{
			if (currentMissile->hasComponent("ExplodingPosition"))
			{
				currentMissile->getComponent("ExplodingPosition")->deleteData();
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

			double velX = currentMissile->getComponent("Velocity")->getDataDouble().at(0);
			double curX = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0);
			double expX = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0);
			double velY = currentMissile->getComponent("Velocity")->getDataDouble().at(1);
			double curY = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1);
			double expY = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1);
			
			if (sqrt(pow(expX - curX - velX, 2) + pow(expY - curY - velY, 2)) > sqrt(pow(expX - curX + velX, 2) + pow(expY - curY + velY, 2)))
			{
				double temp = currentMissile->getComponent("Velocity")->getDataDouble().at(0);
				temp *= -1;
				currentMissile->getComponent("Velocity")->changeData(&temp, 0);
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
				if (missiles.at(i)->getComponent("Life")->getDataBool().at(0))
				{
					if (missiles.at(i)->hasComponent("Slope"))
						slope = missiles.at(i)->getComponent("Slope")->getDataDouble().at(0);
					if (missiles.at(i)->hasComponent("CurrentPosition") && missiles.at(i)->hasComponent("StartingPosition") && missiles.at(i)->hasComponent("Velocity"))
					{
						double theta = atan((missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) - missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1)) / (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) - missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0)));
						theta *= -1;
						double velocity = missiles.at(i)->getComponent("Velocity")->getDataDouble().at(0);
						double lengthX = velocity * cos(theta);
						double lengthY = velocity * sin(theta);

						temp1 = missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) + lengthX;
						temp2 = slope * (temp1 - missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(0)) + -1 * missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(1);
						temp2 *= -1;

						missiles.at(i)->getComponent("Velocity")->deleteData();
						missiles.at(i)->getComponent("Velocity")->addData(velocity);
						missiles.at(i)->getComponent("Velocity")->addData(lengthX);
						missiles.at(i)->getComponent("Velocity")->addData(lengthY);

						missiles.at(i)->getComponent("CurrentPosition")->deleteData();
						missiles.at(i)->getComponent("CurrentPosition")->addData(temp1);
						missiles.at(i)->getComponent("CurrentPosition")->addData(temp2);


						sf::Sprite *s = missiles.at(i)->getComponent("Sprite")->getDataSprite().at(0);
						s->setPosition(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0), missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));
					}
					/*
	<<<<<<< HEAD
	//Adjust Chem Trail
	/*
	if (missiles.at(i)->hasComponent("ChemTrail"))
	=======
	///Adjust Chem Trail if missile is still alive
	if (missiles.at(i)->getComponent("Life")->getDataBool() && missiles.at(i)->hasComponent("ChemTrail"))
	>>>>>>> 840e03cef478361d9c9754d025d4dc94450cfaaf
	{
	line[0] = sf::Vertex(sf::Vector2f(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0)
	, missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1)));
	line[1] = sf::Vertex(sf::Vector2f(missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0)
	, missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1)));
	missiles.at(i)->getComponent("ChemTrail")->deleteData();
	<<<<<<< HEAD
	missiles.at(i)->getComponent("ChemTrail")->addData(temp1);
	missiles.at(i)->getComponent("ChemTrail")->addData(temp2);
	missiles.at(i)->getComponent("ChemTrail")->addData(missiles.at(i)->
	getComponent("CurrentPosition")->getDataDouble().at(0));
	if (missiles.at(i)->hasComponent("CurrentPosition"))
	missiles.at(i)->getComponent("ChemTrail")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));
	}
	=======
	missiles.at(i)->getComponent("ChemTrail")->addData(line);
	}
	>>>>>>> 840e03cef478361d9c9754d025d4dc94450cfaaf
	*/

					//If the current Missile is positioned on its explosion point, (give an error of the velocity amount)

					double velocity = missiles.at(i)->getComponent("Velocity")->getDataDouble().at(0);
					velocity = abs(velocity);
					//Check x values
					if (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) - velocity <=
						missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) &&
						missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) + velocity >=
						missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0))
					{
						//check y values
						if (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) - velocity <=
							missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) &&
							missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) + velocity >=
							missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1))
						{
							//Make the missile explode
							MissileExploder exploder;
							exploder.control(window, missiles.at(i));
							missiles.at(i)->getComponent("Life")->deleteData();
							missiles.at(i)->getComponent("Life")->addData(false);
							missiles.at(i)->getComponent("DrawSprite")->deleteData();
							missiles.at(i)->getComponent("DrawSprite")->addData(false);
							missiles.at(i)->getComponent("Move")->deleteData();
							missiles.at(i)->getComponent("Move")->addData(false);
						}
					}
				}
			}
			MissileExploder exploder;
			exploder.control(window, missiles.at(i));
		}
	}
}
