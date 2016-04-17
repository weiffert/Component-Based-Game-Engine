#include "stdafx.h"
#include "LevelChange.h"

#include <string>
#include <iostream>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"
#include "Property.h"


LevelChange::LevelChange()
{
}


LevelChange::~LevelChange()
{
}

std::string LevelChange::control(SystemManager * systemManager, AssetManager *assetManager, sf::RenderWindow *window)
{
	//If the level is done...
	Entity *launcherAi = systemManager->getMaterial("MissileLauncherAi");
	if (launcherAi->getComponent("CurrentMissileCount")->getDataInt().at(0) <= 0)
	{
		//Determine the number of cities alive
		Entity *city[6] {systemManager->getMaterial("City1"), systemManager->getMaterial("City2"), systemManager->getMaterial("City3"), systemManager->getMaterial("City4"), systemManager->getMaterial("City5"), systemManager->getMaterial("City6")};
		bool life = false;
		int liveCities = 0;
		for (int i = 0; i < 6; i++)
		{
			if (city[i]->getComponent("Life")->getDataBool().at(0) == true)
			{
				life = true;
				liveCities++;
			}
		}
		
		//Determine the number of remaining missiles.
		Entity *base[3] {systemManager->getMaterial("Base1"), systemManager->getMaterial("Base2"), systemManager->getMaterial("Base3")};
		int liveMissiles = 0;
		for (int i = 0; i < 3; i++)
		{
			liveMissiles += base[i]->getComponent("CurrentMissileCount")->getDataInt().at(0);
		}

		//Add points.
		Property *points = systemManager->getMaterial("Player")->getComponent("Points");
		Property *scoreMultiplyer = systemManager->getMaterial("Player")->getComponent("PointsPerLiveCity");
		for (int i = 0; i < liveCities; i++)
		{
			int oldPoints = points->getDataInt().at(0);
			oldPoints += scoreMultiplyer->getDataInt().at(0); 
			points->deleteData();
			points->addData(oldPoints);
		}

		scoreMultiplyer = systemManager->getMaterial("Player")->getComponent("PointsPerUnusedMissile");
		for (int i = 0; i < liveCities; i++)
		{
			int oldPoints = points->getDataInt().at(0);
			oldPoints += scoreMultiplyer->getDataInt().at(0);
			points->deleteData();
			points->addData(oldPoints);
		}

		//Update points text.
		systemManager->getMaterial("Player")->getComponent("Text")->getDataText().at(0)->setString(std::to_string(points->getDataInt().at(0)));
		
		//Award bonus city.
		int bonusCityThreshold = systemManager->getMaterial("Player")->getComponent("BonusCityThreshold")->getDataInt().at(0);
		if (points->getDataInt().at(0) >= bonusCityThreshold)
		{
			if (liveCities != 6)
			{
				bool set = false;
				int place;
				while (!set)
				{
					place = rand() % 6 + 1;
					
					if (city[place]->getComponent("Life")->getDataBool().at(0) == false)
					{
						set = true; 
						city[place]->getComponent("Life")->deleteData();
						city[place]->getComponent("Life")->addData(true);
						city[place]->getComponent("Draw")->deleteData();
						city[place]->getComponent("Draw")->addData(true);
						city[place]->getComponent("DrawSprite")->deleteData();
						city[place]->getComponent("DrawSprite")->addData(true);
						systemManager->getMaterial("Player")->getComponent("BonusCityThreshold")->deleteData();
						systemManager->getMaterial("Player")->getComponent("BonusCityThreshold")->addData(bonusCityThreshold + systemManager->getMaterial("Player")->getComponent("BonusCityIncrement")->getDataInt().at(0));
					}
				}
			}
		}

		//Determine if the game is done.
		life = false;
		for (int i = 0; i < 6; i++)
		{
			if (city[i]->getComponent("Life")->getDataBool().at(0) == true)
			{
				life = true;
			}
		}

		if (!life)
		{
			return "GameOver";
		}

	}
	else
	{
		return "constant";
	}
}