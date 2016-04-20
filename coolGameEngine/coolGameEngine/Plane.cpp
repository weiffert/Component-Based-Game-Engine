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


Plane::Plane(int totalMis, int currMis, int height, SystemManager * s, AssetManager *a)
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
	std::vector<Entity *> missiles = systemManager->getMaterial("MissileLauncherAi")->getComponent("MissilesHeld")->getDataEntity();
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
	Entity *temp = nullptr;
	sf::Sprite * plane = nullptr;
	Entity * currentPlane = nullptr;
	MissileLauncherAi missileLauncherAi(assetManager, systemManager);
	std::vector<Entity*> missiles;
	bool collision = false;

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
						if (this->intersection((temp->getComponent("CircleShape")->getDataCircleShape().at(0)), currentPlane->getComponent("Sprite")->getDataSprite().at(0)))
						{
							collision = true;
						}
					}
				}
			}
			if (collision)
			{
				currentPlane->getComponent("Draw")->deleteData();
				currentPlane->getComponent("Draw")->addData(false);
				currentPlane->getComponent("Life")->deleteData();
				currentPlane->getComponent("Life")->addData(false);
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

	sf::Sprite * satellite = plane->getComponent("Sprite")->getDataSprite().at(0);
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
	do {
		yHeight = rand() % 400;
	} while (yHeight > 150);

	plane->getComponent("CurrentPosition")->addData(yHeight);

	//Make it either a satellite or a plane (default is plane)  >>>>>>>>>>>> THESE TEXTURES ARE NOT WORKING <<<<<<<<<<<<<
	if (rand() % 2 == 0)
	{
		//Make it a Satellite
		sf::Texture texture;
		if (texture.loadFromFile("Satellite.png"))
			satellite->setTexture(texture);
		else
		{
			if (texture.loadFromFile("Plane.png"))
				satellite->setTexture(texture);
		}
		sf::Sprite *satellite = plane->getComponent("Sprite")->getDataSprite().at(0);
		if (!texture.loadFromFile("satellite.png"))
			std::cout << "Failed to load satellite.png" << std::endl;
		satellite->setTexture(texture);

		assetManager->add(&texture);
	}

	//This is done just so you can see a white box where the plane should be
	sf::Texture texture;
	texture.loadFromFile("Satellite.png");
	satellite->setTexture(texture);

	//Scale the plane
	float scaleY = 30 / satellite->getLocalBounds().height;
	float scaleX = 40 / satellite->getLocalBounds().width;
	satellite->setScale(sf::Vector2f(scaleX, scaleY));

	//Set other values

	delete direction;
}


bool Plane::intersection(sf::CircleShape * explosion, sf::Sprite * plane)
{
	//Checks if sprite contains any "extreme" point on the circle (top, bottom, far left, far right)
	bool collision = false;
	sf::Vector2f center = { sf::Vector2f((sf::FloatRect(explosion->getGlobalBounds()).left) + (sf::FloatRect(explosion->getGlobalBounds()).width / 2),
		(sf::FloatRect(explosion->getGlobalBounds()).top) + sf::FloatRect(explosion->getGlobalBounds()).height / 2) };
	sf::Vector2f distance;

	//Checks if the circle is inside
	if (plane->getGlobalBounds().contains(center))
		collision = true;

	//Far right
	if (plane->getGlobalBounds().contains(sf::Vector2f(center.x + explosion->getRadius(), center.y)))
		collision = true;
	//Far Left
	if (plane->getGlobalBounds().contains(sf::Vector2f(center.x - explosion->getRadius(), center.y)))
		collision = true;
	//Bottom
	if (plane->getGlobalBounds().contains(sf::Vector2f(center.x, center.y + explosion->getRadius())))
		collision = true;
	//Top
	if (plane->getGlobalBounds().contains(sf::Vector2f(center.x, center.y - explosion->getRadius())))
		collision = true;

	//Check if circle contains the extreme points of the sprite (each corner)
	sf::Vector2f topLeftCorner = { plane->getGlobalBounds().top, plane->getGlobalBounds().left };
	sf::Vector2f topRightCorner = { plane->getGlobalBounds().top, plane->getGlobalBounds().left + plane->getGlobalBounds().width };
	sf::Vector2f bottomLeftCorner = { plane->getGlobalBounds().top + plane->getGlobalBounds().height, plane->getGlobalBounds().left };
	sf::Vector2f bottomRightCorner = { plane->getGlobalBounds().top + plane->getGlobalBounds().height, plane->getGlobalBounds().left + plane->getGlobalBounds().width };

	if (pointIntersection(*explosion, topLeftCorner) || pointIntersection(*explosion, topRightCorner) || pointIntersection(*explosion, bottomLeftCorner) || pointIntersection(*explosion, bottomRightCorner))
		collision = true;

	return collision;
}


bool Plane::pointIntersection(sf::CircleShape circle, sf::Vector2f point)
{
	float radius = circle.getLocalBounds().height / 2;
	sf::Vector2f distance;
	sf::Vector2f center;
	bool intersects = false;

	//Change in x from center of sprite to outside
	center = sf::Vector2f((sf::FloatRect(circle.getGlobalBounds()).left) + (sf::FloatRect(circle.getGlobalBounds()).width / 2), (sf::FloatRect(circle.getGlobalBounds()).top) + sf::FloatRect(circle.getGlobalBounds()).height / 2);
	distance.x = point.x - center.x;
	distance.y = point.y - center.y;
	if (distance.x * distance.x + distance.y * distance.y <= radius * radius)
		intersects = true;

	return intersects;
}