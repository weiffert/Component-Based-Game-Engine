#include "Plane.h"

#include <stdlib.h> 
#include <time.h>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "MissileExploder.h"
#include "Property.h"
#include "Entity.h"


Plane::Plane()
{
  totalMissiles = 10;
  missilesLeft = 10;
}

Plane::Plane(int totalMis, int currMis)
{
  totalMissiles = totalMis;
  missilesLeft = currMis;
}

void Plane::setTargets()
{
 //Shortened
    srand(time(NULL));
  
    targetOne = rand() % 6 + 1;
    
    targetTwo = rand() % 6 + 1;
    
    while(targetTwo == targetOne)
    {
        targetTwo = rand() % 6 + 1;
    }
    
    targetThree = rand() % 6 + 1;
    
    while(targetThree == targetOne || targetThree == targetTwo)
    {
        targetThree = rand() % 6 + 1;
    }
}

int Plane::launchMissiles(SystemManager* systemManager, Entity *currentMissile, sf::RenderWindow *window)
{
	//Shoots missile if it has missiles left
	setTargets();
	if (missilesLeft > 0)
	{
		srand(time(NULL));
		int missileTarget = rand() % 3 + 1;

		//Delete data for exploding position and starting position for missile
		if (currentMissile->hasComponent("StartingPosition"))
			currentMissile->getComponent("StartingPosition")->deleteData();
		if (currentMissile->hasComponent("ExplodingPosition"))
			currentMissile->getComponent("ExplodingPosition")->deleteData();


		if (missileTarget != 1)
		{
			//Push back new values with starting and ending positions
			if (targetOne == 1 || targetTwo == 1 || targetThree == 1)
			{
				//set position to the first city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(150);
			}

			else if (targetOne == 2 || targetTwo == 2 || targetThree == 2)
			{
				//set position to the second city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(180);
			}

			else if (targetOne == 3 || targetTwo == 3 || targetThree == 3)
			{
				//set position to the third city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(210);
			}

			else if (targetOne == 4 || targetTwo == 4 || targetThree == 4)
			{
				//set position to the fourth city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(270);
			}

			else if (targetOne == 5 || targetTwo == 5 || targetThree == 5)
			{
				//set position to the fifth city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(300);
			}

			else if (targetOne == 6 || targetTwo == 6 || targetThree == 6)
			{
				//set position to the sixth city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(330);
			}
		}
		else
		{
			int x = rand() % 3 + 1;

			if (x == 1)
			{
				currentMissile->getComponent("ExplodingPosition")->addData(80); //y for Base1
				currentMissile->getComponent("ExplodingPosition")->addData(120); //x for Base1
			}
			else if (x == 2)
			{
				currentMissile->getComponent("ExplodingPosition")->addData(80); //y for Base2
				currentMissile->getComponent("ExplodingPosition")->addData(240); //x for Base2
			}
			else
			{
				currentMissile->getComponent("ExplodingPosition")->addData(80); //y for Base3
				currentMissile->getComponent("ExplodingPosition")->addData(360); //x for Base3
			}

		}
		//What does this do?
		currentMissile->getComponent("StartingPosition")->deleteData();

		currentMissile->getComponent("StartingPosition")->addData(systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->getDataDouble().at(0));
	
		currentMissile->getComponent("StartingPosition")->addData(systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->getDataDouble().at(1));

		//Sets slope (Which is x/y)
		currentMissile->getComponent("Slope")->deleteData();

		int changeX = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0) -
			currentMissile->getComponent("StartingPosition")->getDataDouble().at(0);

		int changeY = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1) -
			currentMissile->getComponent("StartingPosition")->getDataDouble().at(1);

		currentMissile->getComponent("Slope")->addData(setSlope(changeX, changeY));

		currentMissile->getComponent("Fired")->deleteData();
		currentMissile->getComponent("Fired")->addData(true);

		//Decrease missiles left
		missilesLeft--;
		return 1;
	}

	//If it doesn't, do not fire and possibly tell the user
	return 0;
}

double Plane::setSlope(int pathX, int pathY)
{
  double speedX;
  
  speedX = double(pathX) / double(pathY);
  
  return speedX;
}

void Plane::update(sf::RenderWindow *window, Entity *launcherAi, SystemManager *systemManager)
{
	double slope;
	
	double tempPosition = systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->getDataDouble().at(0);
	tempPosition += 1;
	systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->deleteData();
	systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->addData(tempPosition);
	systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->addData(0);

	//Goes through all the missiles
	for (int i = 0; i < 5; i++)
	{
		std::vector<Entity *> missiles = launcherAi->getComponent("MissilesHeld")->getDataEntity();
		if (missiles.at(i)->hasComponent("Fired"))
		{
			if (missiles.at(i)->getComponent("Fired")->getDataBool().at(0))
			{
				slope = missiles.at(i)->getComponent("Slope")->getDataDouble().at(0);
				missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) += slope;
				missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) -= 1;
				sf::Sprite *sprite = missiles.at(i)->getComponent("Sprite")->getDataSprite().at(0);
				sprite->move(slope, -1);
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
						MissileExploder missileExploder;
						missileExploder.control(window, missiles.at(i));
						missiles.at(i)->getComponent("Life")->deleteData();
						missiles.at(i)->getComponent("Life")->addData(false);
					}
				}
			}
		}
	}
}
