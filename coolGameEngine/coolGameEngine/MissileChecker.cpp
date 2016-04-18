#include "MissileChecker.h"

#include <SFML/Graphics.hpp>

#include "SystemManager.h"
#include "Property.h"
#include "Entity.h"

//Controllers
#include "MissileExploder.h"

MissileChecker::MissileChecker()
{
}

MissileChecker::~MissileChecker()
{
}

void MissileChecker::control(sf::RenderWindow * window, SystemManager * systemManager)
{
  //Goes through each enemy missile and determines if they should explode, if they should explode call on MissileExploder
	MissileExploder exploder;
	Entity *currentMissile = nullptr;
	Entity *currentBase = nullptr;
	Entity *temp = nullptr;
	sf::Vector2f position;
	bool collision = false;

	Entity *launcherAi = systemManager->getMaterial("MissileLauncherAi");
	for (int i = launcherAi->getComponent("CurrentMissileCount")->getDataInt().at(0); i < launcherAi->getComponent("TotalMissileCount")->getDataInt().at(0); i++)
	{
		currentMissile = launcherAi->getComponent("MissilesHeld")->getDataEntity().at(i);
		position.x = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0);
		position.y = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1);
		//Go through each active missile and see if it is colliding with a circle shape from any missile explosion
		if (currentMissile->getComponent("Fired")->getDataBool().at(0) && currentMissile->getComponent("Life")->getDataBool().at(0))
		{
			//Check to see if it is colliding with a user fired missile explosion
			//Base1
			currentBase = systemManager->getMaterial("Base1");
			for (int u = currentBase->getComponent("CurrentMissileCount")->getDataInt().at(0); u < currentBase->getComponent("TotalMissileCount")->getDataInt().at(0); u++)
			{
				temp = currentBase->getComponent("MissilesHeld")->getDataEntity().at(u);
				//Makes sure that explosion is not done and has not started
				if (temp->getComponent("Explode")->getDataBool().at(0))
				{
					if (temp->hasComponent("CircleShape"))
						if (this->intersection(*temp->getComponent("CircleShape")->getDataCircleShape().at(0), position))
						{
							collision = true;
						}
				}
			}

			//Base2
			currentBase = systemManager->getMaterial("Base2");
			for (int u = currentBase->getComponent("CurrentMissileCount")->getDataInt().at(0); u < currentBase->getComponent("TotalMissileCount")->getDataInt().at(0); u++)
			{
				temp = currentBase->getComponent("MissilesHeld")->getDataEntity().at(u);
				//Makes sure that explosion is not done and has not started
				if (temp->getComponent("Explode")->getDataBool().at(0))
				{
					if (temp->hasComponent("CircleShape"))
						if (this->intersection(*temp->getComponent("CircleShape")->getDataCircleShape().at(0), position))
						{
							collision = true;
						}
				}
			}

			//Base3
			currentBase = systemManager->getMaterial("Base3");
			for (int u = currentBase->getComponent("CurrentMissileCount")->getDataInt().at(0); u < currentBase->getComponent("TotalMissileCount")->getDataInt().at(0); u++)
			{
				temp = currentBase->getComponent("MissilesHeld")->getDataEntity().at(u);
				//Makes sure that explosion is not done and has not started
				if (temp->getComponent("Explode")->getDataBool().at(0))
				{
					if (temp->hasComponent("CircleShape"))
						if (this->intersection(*temp->getComponent("CircleShape")->getDataCircleShape().at(0), position))
						{
							collision = true;
						}
				}
			}

			//Check for enemy missile explosions
			for (int u = launcherAi->getComponent("CurrentMissileCount")->getDataInt().at(0); u < launcherAi->getComponent("TotalMissileCount")->getDataInt().at(0); u++)
			{
				temp = launcherAi->getComponent("MissilesHeld")->getDataEntity().at(u);
				if (temp->getComponent("ExplosionPhase")->getDataInt().at(0) == 1)
				{
					if (temp->hasComponent("CircleShape"))
						if (this->intersection(*temp->getComponent("CircleShape")->getDataCircleShape().at(0), position))
						{
							collision = true;
						}
				}
			}
		}
		if (collision)
		{
			currentMissile->getComponent("Life")->deleteData();
			currentMissile->getComponent("Life")->addData(false);
			currentMissile->getComponent("DrawSprite")->deleteData();
			currentMissile->getComponent("DrawSprite")->addData(false);
			currentMissile->getComponent("DrawCircleShape")->deleteData();
			currentMissile->getComponent("DrawCircleShape")->addData(true);
			currentMissile->getComponent("DrawRectangleShape")->deleteData();
			currentMissile->getComponent("DrawRectangleShape")->addData(false);
			currentMissile->getComponent("Move")->deleteData();
			currentMissile->getComponent("Move")->addData(false);
			currentMissile->getComponent("Explode")->deleteData();
			currentMissile->getComponent("Explode")->addData(true);
			exploder.control(window, currentMissile);
			sf::CircleShape *c = currentMissile->getComponent("CircleShape")->getDataCircleShape().at(0);
			c->setPosition(currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0), currentMissile ->getComponent("CurrentPosition")->getDataDouble().at(1));
		}
	}
}


bool MissileChecker::intersection(sf::CircleShape circle, sf::Vector2f point)
{
	float radius = circle.getLocalBounds().height / 2;
	sf::Vector2f distance;
	sf::Vector2f center;
	bool intersects = false;

	//Change in x from center of sprite to outside
	center = sf::Vector2f((sf::FloatRect(circle.getGlobalBounds()).left) + (sf::FloatRect(circle.getGlobalBounds()).width/2), (sf::FloatRect(circle.getGlobalBounds()).top) + sf::FloatRect(circle.getGlobalBounds()).height /2);
	distance.x = point.x - center.x;
	distance.y = point.y - center.y;
	if (distance.x * distance.x + distance.y * distance.y <= radius * radius)
		intersects = true;

	return intersects;
}