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
#include "MissileExploder.h"
#include "MissileChecker.h"


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


Plane::Plane(int totalMis, int currMis, int height, SystemManager * s, AssetManager *a)
{
	totalMissiles = totalMis;
	missilesLeft = currMis;
	systemManager = s;
	assetManager = a;
	Property *currentPosition = systemManager->getMaterial("Plane")->getComponent("CurrentPosition");
	currentPosition->deleteData();
	currentPosition->addData(height);
	currentPosition->addData(0);
}


Plane::~Plane()
{

}


void Plane::update(sf::RenderWindow *window)
{
	double slope;
	double temp1, temp2;
	double length;
	int planeNumber = 1;
	sf::Vector2f rectLength;
	Entity *temp = nullptr;
	sf::Sprite * plane = nullptr;
	Entity * currentPlane = nullptr;
	MissileLauncherAi missileLauncherAi(assetManager, systemManager);
	std::vector<Entity*> missiles;
	bool collision = false;

	do
	{
		collision = false;
		if (planeNumber == 1)
		{
			currentPlane = systemManager->getMaterial("Plane1");
		}
		if (planeNumber == 2)
		{
			currentPlane = systemManager->getMaterial("Plane2");
		}
		if (planeNumber == 3)
		{
			currentPlane = systemManager->getMaterial("Plane3");
		}

		if (currentPlane->getComponent("Draw")->getDataBool().at(0)) //Makes sure current plane is active
		{
			//Checks for collisions
			std::vector<Entity *> explodingMissiles = systemManager->getComponent("ExplodingMissiles")->getDataEntity();
			for (int u = 0; u < explodingMissiles.size(); u++)
			{
				temp = explodingMissiles.at(u);
				//Makes sure that explosion is not done and has not started
				if (temp->getComponent("Explode")->getDataBool().at(0))
				{
					if (temp->hasComponent("CircleShape"))
					{
						MissileChecker checker;
						if (checker.intersection(temp, temp->getComponent("CircleShape")->getDataCircleShape().at(0), currentPlane->getComponent("Sprite")->getDataSprite().at(0)))
						{
							collision = true;
						}
					}
				}
			}
			if ((collision || currentPlane->getComponent("Explode")->getDataBool().at(0)) /*&& currentPlane->getComponent("Life")->getDataBool().at(0)*/) //Makes sure its doing more than once. This does not work. Life is set to false in the next statement. Besides, after the explosion is done, explode == false;
			{
				if (currentPlane->getComponent("Life")->getDataBool().at(0))
				{
					//Make explosion sound (from a missile)
					sf::Sound * sound = new sf::Sound;
					sound->setBuffer(*currentPlane->getComponent("SoundMissileExplosion")->getDataSoundBuffer().at(0));
					assetManager->add(sound);
					sound->play();
				}
				currentPlane->getComponent("Life")->deleteData();
				currentPlane->getComponent("Life")->addData(false);
				currentPlane->getComponent("DrawSprite")->deleteData();
				currentPlane->getComponent("DrawSprite")->addData(false);
				currentPlane->getComponent("DrawCircleShape")->deleteData();
				currentPlane->getComponent("DrawCircleShape")->addData(true);
				currentPlane->getComponent("Move")->deleteData();
				currentPlane->getComponent("Move")->addData(false);
				currentPlane->getComponent("Explode")->deleteData();
				currentPlane->getComponent("Explode")->addData(true);
				currentPlane->getComponent("ShotDown")->deleteData();
				currentPlane->getComponent("ShotDown")->addData(true);
				sf::CircleShape *c = currentPlane->getComponent("CircleShape")->getDataCircleShape().at(0);
				c->setPosition(currentPlane->getComponent("CurrentPosition")->getDataDouble().at(0), currentPlane->getComponent("CurrentPosition")->getDataDouble().at(1));

				//Covered in MissileExploder.
				//scoreKeeper.increaseScore(50, systemManager->getMaterial("Player"));

				MissileExploder explode;
				explode.control(systemManager, window, currentPlane);
			}
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
			if (temp1 < 0 || temp1 > 480)
			{
				currentPlane->getComponent("Life")->deleteData();
				currentPlane->getComponent("Life")->addData(false);
				currentPlane->getComponent("Draw")->deleteData();
				currentPlane->getComponent("Draw")->addData(false);
			}

			//Call on launcher
			if (currentPlane->getComponent("Life")->getDataBool().at(0))
				this->launchMissiles(window);
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


int Plane::launchMissiles(sf::RenderWindow *window)
{
	Entity * plane = nullptr;
	Entity *missile = nullptr;
	Entity *launcherAi = systemManager->getMaterial("MissileLauncherAi");
	std::vector<Entity *> missiles = systemManager->getMaterial("MissileLauncherAi")->getComponent("MissilesHeld")->getDataEntity();
	MissileLauncherAi launcher(assetManager, systemManager);

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
			if (rand() % launcherAi->getComponent("FireRate")->getDataInt().at(0) == 0)
			{
				//Checks if there are missiles left to fire
				int decrement = launcherAi->getComponent("CurrentMissileCount")->getDataInt().at(0) - 1;
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

					//Fire from plane
					missile->getComponent("StartingPosition")->deleteData();
					missile->getComponent("StartingPosition")->addData(plane->getComponent("CurrentPosition")->getDataDouble().at(0));
					missile->getComponent("StartingPosition")->addData(plane->getComponent("CurrentPosition")->getDataDouble().at(1));

					missile->getComponent("CurrentPosition")->deleteData();
					missile->getComponent("CurrentPosition")->addData(plane->getComponent("CurrentPosition")->getDataDouble().at(0));
					missile->getComponent("CurrentPosition")->addData(plane->getComponent("CurrentPosition")->getDataDouble().at(1));

					launcher.launchMissiles(missile, window);
				}
			}
		}
	}
	//If it doesn't, do not fire and possibly tell the user
	return 0;
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

	sf::Sprite *satellite = plane->getComponent("Sprite")->getDataSprite().at(0);

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
	do {
		yHeight = rand() % 400;
	} while (yHeight > 150);

	plane->getComponent("CurrentPosition")->addData(yHeight);

	//Make it either a satellite or a plane.
	sf::Texture *texture = new sf::Texture;
	if (rand() % 2 == 0)
	{
		if (!texture->loadFromFile("satellite.png"))
			std::cout << "Failed to load satellite.png" << std::endl;
	}
	else
	{
		if (*direction == "Right")
		{
			if (!texture->loadFromFile("plane.png"))
				std::cout << "Failed to load plane.png" << std::endl;
		}
		else
		{
			if (!texture->loadFromFile("plane-other-direction.png"))
				std::cout << "Failed to load plane-other-direction.png" << std::endl;
		}
	}

	satellite->setTexture(*texture, true);
	satellite->setOrigin(satellite->getLocalBounds().width / 2, satellite->getLocalBounds().height/2);

	assetManager->add(texture);

	//Set other values
	//Sets draw to true which shows it is on the screen
	plane->getComponent("Draw")->deleteData();
	plane->getComponent("Draw")->addData(true);
	plane->getComponent("Life")->deleteData();
	plane->getComponent("Life")->addData(true);
	plane->getComponent("DrawSprite")->deleteData();
	plane->getComponent("DrawSprite")->addData(true);
	plane->getComponent("DrawCircleShape")->deleteData();
	plane->getComponent("DrawCircleShape")->addData(false);
	plane->getComponent("Move")->deleteData();
	plane->getComponent("Move")->addData(true);
	plane->getComponent("Explode")->deleteData();
	plane->getComponent("Explode")->addData(false);

	delete direction;
}


double Plane::setSlope(double pathX, double pathY)
{
	double speedX;

	speedX = pathX / pathY;

	return speedX;
}