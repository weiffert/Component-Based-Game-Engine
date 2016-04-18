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
		bool life = false;
		for (int i = 0; i < launcherAi->getComponent("TotalMissileCount")->getDataInt().at(0); i++)
		{
			if (launcherAi->getComponent("MissilesHeld")->getDataEntity().at(i)->getComponent("Life")->getDataBool().at(0) == true || launcherAi->getComponent("MissilesHeld")->getDataEntity().at(i)->getComponent("Explode")->getDataBool().at(0) == true)
				life = true;
		}
		
		if (!life)
		{
			if (systemManager->getMaterial("Player")->getComponent("LevelFinished")->getDataBool().at(0) == false)
			{
				systemManager->getMaterial("Player")->getComponent("LevelFinished")->deleteData();
				systemManager->getMaterial("Player")->getComponent("LevelFinished")->addData(true);

				//Determine the number of cities alive
				Entity *city[6] {systemManager->getMaterial("City1"), systemManager->getMaterial("City2"), systemManager->getMaterial("City3"), systemManager->getMaterial("City4"), systemManager->getMaterial("City5"), systemManager->getMaterial("City6")};
				life = false;
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
				for (int i = 0; i < liveMissiles; i++)
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
				//Reset values and increment proper values.
				else
				{
					systemManager->getMaterial("Player")->getComponent("LevelFinished")->deleteData();
					systemManager->getMaterial("Player")->getComponent("LevelFinished")->addData(false);

					Entity *temp = systemManager->getMaterial("MissileLauncherAi");
					temp->getComponent("CurrentMissileCount")->deleteData();
					temp->getComponent("CurrentMissileCount")->addData(temp->getComponent("TotalMissileCount")->getDataInt().at(0));
					
					int fireRate = temp->getComponent("FireRate")->getDataInt().at(0);
					temp->getComponent("FireRate")->deleteData();
					temp->getComponent("FireRate")->addData(fireRate - temp->getComponent("FireRateIncrement")->getDataInt().at(0));
					
					int splitChance = temp->getComponent("SplitChance")->getDataInt().at(0);
					temp->getComponent("SplitChance")->deleteData();
					temp->getComponent("SplitChance")->addData(splitChance - temp->getComponent("SplitChanceIncrement")->getDataInt().at(0));
					
					temp->getComponent("SetTargets")->deleteData();
					temp->getComponent("SetTargets")->addData(false);

					for (int i = 0; i < temp->getComponent("TotalMissileCount")->getDataInt().at(0); i++)
					{
						Entity *missile = temp->getComponent("MissilesHeld")->getDataEntity().at(i);
						missile->getComponent("Fired")->deleteData();
						missile->getComponent("Fired")->addData(false);
						missile->getComponent("Draw")->deleteData();
						missile->getComponent("Draw")->addData(true);
						missile->getComponent("DrawSprite")->deleteData();
						missile->getComponent("DrawSprite")->addData(true);
						missile->getComponent("DrawCircleShape")->deleteData();
						missile->getComponent("DrawCircleShape")->addData(false);
						missile->getComponent("DrawRectangleShape")->deleteData();
						missile->getComponent("DrawRectangleShape")->addData(false);
						missile->getComponent("Move")->deleteData();
						missile->getComponent("Move")->addData(false);
						missile->getComponent("Explode")->deleteData();
						missile->getComponent("Explode")->addData(false);
						missile->getComponent("Split")->deleteData();
						missile->getComponent("Split")->addData(false);
						missile->getComponent("SplitFired")->deleteData();
						missile->getComponent("SplitFired")->addData(false);
						missile->getComponent("Life")->deleteData();
						missile->getComponent("Life")->addData(true);
						missile->getComponent("ExplosionPhase")->deleteData();
						missile->getComponent("ExplosionPhase")->addData(0);

						sf::RectangleShape *r = missile->getComponent("RectangleShape")->getDataRectangleShape().at(0);
						r->setSize(sf::Vector2f(0, 2));

						int oldVelocity = missile->getComponent("Velocity")->getDataDouble().at(0);
						missile->getComponent("Velocity")->deleteData();
						missile->getComponent("Velocity")->addData(oldVelocity * 2);
						missile->getComponent("Velocity")->addData(0);
						missile->getComponent("Velocity")->addData(0);
					}

					Entity *base[3] {systemManager->getMaterial("Base1"), systemManager->getMaterial("Base2"), systemManager->getMaterial("Base3")};
					for (int i = 0; i < 3; i++)
					{
						base[i]->getComponent("CurrentMissileCount")->deleteData();
						base[i]->getComponent("CurrentMissileCount")->addData(base[i]->getComponent("TotalMissileCount")->getDataInt().at(0));
						base[i]->getComponent("Text")->getDataText().at(0)->setString("");
						
						for (int j = 0; j < base[i]->getComponent("TotalMissileCount")->getDataInt().at(0); i++)
						{
							Entity *missile = base[i]->getComponent("MissilesHeld")->getDataEntity().at(j);
							missile->getComponent("Fired")->deleteData();
							missile->getComponent("Fired")->addData(false);
							missile->getComponent("Draw")->deleteData();
							missile->getComponent("Draw")->addData(true);
							missile->getComponent("DrawSprite")->deleteData();
							missile->getComponent("DrawSprite")->addData(true);
							missile->getComponent("DrawCircleShape")->deleteData();
							missile->getComponent("DrawCircleShape")->addData(false);
							missile->getComponent("DrawRectangleShape")->deleteData();
							missile->getComponent("DrawRectangleShape")->addData(false);
							missile->getComponent("Move")->deleteData();
							missile->getComponent("Move")->addData(false);
							missile->getComponent("Explode")->deleteData();
							missile->getComponent("Explode")->addData(false);
							missile->getComponent("Life")->deleteData();
							missile->getComponent("Life")->addData(true);
							missile->getComponent("ExplosionPhase")->deleteData();
							missile->getComponent("ExplosionPhase")->addData(0);

							missile->getComponent("CurrentPosition")->deleteData();
							missile->getComponent("CurrentPosition")->addData(missile->getComponent("StartingPosition")->getDataDouble().at(0));
							missile->getComponent("CurrentPosition")->addData(missile->getComponent("StartingPosition")->getDataDouble().at(1));

							sf::Sprite *s = missile->getComponent("Sprite")->getDataSprite().at(0);
							s->setPosition(missile->getComponent("SpriteStartPosition")->getDataDouble().at(0), missile->getComponent("SpriteStartPosition")->getDataDouble().at(0));

							sf::Texture *texture = new sf::Texture;
							if (!texture->loadFromFile("missile.png"))
								std::cout << "Failed to load missile.png" << std::endl;
							s->setTexture(*texture);
							assetManager->add(texture);

							int oldVelocity = missile->getComponent("Velocity")->getDataDouble().at(0);
							missile->getComponent("Velocity")->addData(oldVelocity);
							missile->getComponent("Velocity")->addData(0);
							missile->getComponent("Velocity")->addData(0);

							sf::RectangleShape *r = missile->getComponent("RectangleShape")->getDataRectangleShape().at(0);
							r->setSize(sf::Vector2f(0, 2));
						}
					}
					systemManager->getMaterial("Welcome")->getComponent("Text")->getDataText().at(0)->setString("Press any key to continue");
					return "Welcome1";
				}
			}
		}
	}
	return "constant";
}