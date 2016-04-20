#include "Plane.h"

#include <stdlib.h> 
#include <time.h>
#include <iostream>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "Property.h"
#include "Entity.h"

#include "MissileLauncherAi.h"


Plane::Plane()
{
  totalMissiles = 10;
  missilesLeft = 10;

  systemManager = nullptr;
  assetManager = nullptr;
}


Plane::Plane(SystemManager *s, AssetManager *a)
{
	systemManager = s;
	assetManager = a;
}


Plane::Plane(int totalMis, int currMis, int height , SystemManager * s, AssetManager *a)
{
  totalMissiles = totalMis;
  missilesLeft = currMis;
  systemManager = s;
  assetManager = a;
  systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->deleteData();
  systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->addData(height);
  systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->addData(0);
}


Plane::~Plane()
{

}


int Plane::launchMissiles(sf::RenderWindow *window)
{		
	Entity * plane = nullptr;
	Entity *missile = nullptr;
	std::vector<Entity *> missiles = systemManager->getMaterial("LauncherAi")->getComponent("MissilesHeld")->getDataEntity();
	MissileLauncherAi launcher;

	//Go through each active plane
	for (int i = 1; i < 4; i++)
	{
		if (i == 1)
			plane = systemManager->getMaterial("Plane1");
		if (i == 2)
			plane = systemManager->getMaterial("Plane2");
		if (i == 3)
			plane = systemManager->getMaterial("Plane3");

		if (plane->getComponent("Draw")->getDataBool().at(0))
		{
			//Random chance to fire missiles
			if (rand() % plane->getComponent("FireRate")->getDataInt().at(0) == 0)
			{
				//Checks if there are missiles left to fire
				int decrement = 29;
				bool found = false;
				
				while (!found && decrement >= 0)
				{
					if (missiles.at(decrement)->hasComponent("Fired"))
					{
						if (missiles.at(decrement)->getComponent("Fired")->getDataBool().at(0) == false)
						{
							found = true;
							missile = missiles.at(decrement);
						}
					}
					decrement--;
				}
				if (found)
				{
					//sets missile to have been split
					missile->getComponent("Split")->deleteData();
					missile->getComponent("Split")->addData(true);

					missile->getComponent("SplitFired")->deleteData();
					missile->getComponent("SplitFired")->addData(true);

					missile->getComponent("StartingPosition")->deleteData();
					missile->getComponent("StartingPosition")->addData(plane->getComponent("CurrentPosition")->getDataDouble().at(0));
					missile->getComponent("StartingPosition")->addData(plane->getComponent("CurrentPosition")->getDataDouble().at(1));

					missile->getComponent("CurrentPosition")->deleteData();
					missile->getComponent("CurrentPosition")->addData(plane->getComponent("CurrentPosition")->getDataDouble().at(0));
					missile->getComponent("CurrentPosition")->addData(plane->getComponent("CurrentPosition")->getDataDouble().at(1));

					launcher.launchMissiles(missile, window);
				}

					//Set as split fired so it does not start at the top
			}
		}
	}
	//If it doesn't, do not fire and possibly tell the user
	return 0;
}


double Plane::setSlope(double pathX, double pathY)
{
  double speedX;
  
  speedX = pathX / pathY;
  
  return speedX;
}


void Plane::update(sf::RenderWindow *window)
{
	double slope;
	double temp1, temp2;
	double length;
	int planeNumber = 1;
	sf::Vector2f rectLength;
	sf::RectangleShape *temp = nullptr;
	sf::Sprite * plane = nullptr;
	Entity * currentPlane = nullptr;
	MissileLauncherAi missileLauncherAi(assetManager, systemManager);
	std::vector<Entity*> missiles;

	do
	{
		if (planeNumber == 1)
		{
			missiles = systemManager->getMaterial("Plane1")->getComponent("MissilesHeld")->getDataEntity();
			currentPlane = systemManager->getMaterial("Plane1");
		}
		if (planeNumber == 2)
		{
			missiles = systemManager->getMaterial("Plane2")->getComponent("MissilesHeld")->getDataEntity();
			currentPlane = systemManager->getMaterial("Plane2");
		}
		if (planeNumber == 3)
		{
			missiles = systemManager->getMaterial("Plane3")->getComponent("MissilesHeld")->getDataEntity();
			currentPlane = systemManager->getMaterial("Plane3");
		}

		if (currentPlane->getComponent("Draw")->getDataBool().at(0)) //Makes sure current plane is active
		{

			//Moves current plane
			if (currentPlane->getComponent("Direction")->getDataString().at(0) == "Right")
				temp1 = currentPlane->getComponent("CurrentPosition")->getDataDouble().at(0) + currentPlane->getComponent("Velocity")->getDataDouble().at(0);
			else
				temp1 = currentPlane->getComponent("CurrentPosition")->getDataDouble().at(0) - currentPlane->getComponent("Velocity")->getDataDouble().at(0);

			//Set plane location
			plane = currentPlane->getComponent("Sprite")->getDataSprite().at(0);
			plane->setPosition(sf::Vector2f(temp1, currentPlane->getComponent("CurrentPosition")->getDataDouble().at(1)));

			currentPlane->getComponent("CurrentPosition")->changeData(&temp1, 0);

			//If it's off the screen kill the plane
			if (temp1 < 0)
			{
				currentPlane->getComponent("Life")->deleteData();
				currentPlane->getComponent("Life")->addData(false);
			}

		}
		planeNumber++;
	} while (planeNumber < 4);

	//If all planes are inactive, give a random chance of launching a plane
	if (!(systemManager->getMaterial("Plane1")->getComponent("Draw")->getDataBool().at(0) ||
		systemManager->getMaterial("Plane2")->getComponent("Draw")->getDataBool().at(0) ||
		systemManager->getMaterial("Plane3")->getComponent("Draw")->getDataBool().at(0)))
	{
		if (rand() % 5 == 0)
		{
			if (systemManager->getMaterial("Plane1")->getComponent("Life")->getDataBool().at(0))
				this->launchPlane(window, 1);
			else if (systemManager->getMaterial("Plane2")->getComponent("Life")->getDataBool().at(0))
				this->launchPlane(window, 2);
			else if (systemManager->getMaterial("Plane3")->getComponent("Life")->getDataBool().at(0))
				this->launchPlane(window, 3);
		}
	}
}


void Plane::launchPlane(sf::RenderWindow * window, int planeNumber)
{
	Entity * plane = nullptr;
	int yHeight = 0;
	std::string * direction = new std::string; //Avoids linker errors
	srand(time(NULL));

	if (planeNumber == 1)
	{
		plane = systemManager->getMaterial("Plane1");
	}

	else if (planeNumber == 2)
	{
		plane = systemManager->getMaterial("Plane2");
	}

	else
	{
		plane = systemManager->getMaterial("Plane3");
	}

	//Sets draw to true which shows it is on the screen
	plane->getComponent("Draw")->deleteData();
	plane->getComponent("Draw")->addData(true);

	//Determines which way the plane will face
	
	plane->getComponent("CurrentPosition")->deleteData();

	//Left
	if (rand() % 2 == 0)
	{
		*direction = "Left";
		plane->getComponent("Direction")->changeData(direction, 0);

		//Give correct x value
		plane->getComponent("CurrentPosition")->addData(481);//1 greater than screen size
	}

	//Right
	else
	{
		*direction = "Right";
		plane->getComponent("Direction")->changeData(direction, 0);

		//Give correct x value
		plane->getComponent("CurrentPosition")->addData(-1); 
	}

	//Give "random" y height below 400 and above 150
	while (yHeight > 150)
		yHeight = rand() % 400;
	plane->getComponent("CurrentPosition")->addData(yHeight);

	//Make it either a satellite or a plane (default is plane
	if (rand() % 2 == 0)
	{
		//Make it a Satellite
		sf::Sprite *satellite = plane->getComponent("Sprite")->getDataSprite().at(0);
		sf::Texture *texture = new sf::Texture;
		if (!texture->loadFromFile("satellite.png"))
			std::cout << "Failed to load satellite.png" << std::endl;
		satellite->setTexture(*texture);

		assetManager->add(texture);
	}

	

	delete direction;
}