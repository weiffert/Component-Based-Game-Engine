#include "stdafx.h"
#include "LevelChange.h"

#include <string>
#include <iostream>
#include <math.h>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"
#include "Property.h"

#include "ScoreKeeper.h"


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
					if (base[i]->getComponent("Life")->getDataBool().at(0))
						liveMissiles += base[i]->getComponent("CurrentMissileCount")->getDataInt().at(0);
				}

				//Add points.
				ScoreKeeper score;
				Entity *player = systemManager->getMaterial("Player");
				for (int i = 0; i < liveCities; i++)
				{
					score.increaseScore(player->getComponent("PointsPerLiveCity")->getDataInt().at(0), player);
				}


				for (int i = 0; i < liveMissiles; i++)
				{
					score.increaseScore(player->getComponent("PointsPerUnusedMissile")->getDataInt().at(0), player);
				}

				//Award bonus city.
				Property *points = player->getComponent("Points");
				int bonusCityThreshold = systemManager->getMaterial("Player")->getComponent("BonusCityThreshold")->getDataInt().at(0);
				if (points->getDataInt().at(0) >= bonusCityThreshold)
				{
					if (liveCities != 6)
					{
						bool set = false;
						int place;

						//Play bonus city sound.
						sf::Sound * sound = new sf::Sound;
						sound->setBuffer(*systemManager->getComponent("SoundFreeCity")->getDataSoundBuffer().at(0));
						sound->play();
						assetManager->add(sound);

						while (!set)
						{
							place = rand() % 6 + 1;

							if (city[place]->getComponent("Life")->getDataBool().at(0) == false)
							{
								liveCities++;
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

				if (!life)
				{
					return "GameOver";
				}

				//Reset values and increment proper values.
				systemManager->getMaterial("Player")->getComponent("LevelFinished")->deleteData();
				systemManager->getMaterial("Player")->getComponent("LevelFinished")->addData(false);
				systemManager->getMaterial("Player")->getComponent("LevelStart")->deleteData();
				systemManager->getMaterial("Player")->getComponent("LevelStart")->addData(true);

				//Reset MissileLauncherAi
				Entity *temp = systemManager->getMaterial("MissileLauncherAi");
				temp->getComponent("CurrentMissileCount")->deleteData();
				temp->getComponent("CurrentMissileCount")->addData(temp->getComponent("TotalMissileCount")->getDataInt().at(0));

				int fireRate = temp->getComponent("FireRate")->getDataInt().at(0);
				temp->getComponent("FireRate")->deleteData();
				temp->getComponent("FireRate")->addData(fireRate - temp->getComponent("FireRateIncrement")->getDataInt().at(0));

				int splitChance = temp->getComponent("SplitChance")->getDataInt().at(0);
				temp->getComponent("SplitChance")->deleteData();
				temp->getComponent("SplitChance")->addData(splitChance - temp->getComponent("SplitChanceIncrement")->getDataInt().at(0));

				int smartBombChance = temp->getComponent("SmartBombChance")->getDataInt().at(0);
				temp->getComponent("SmartBombChance")->deleteData();
				temp->getComponent("SmartBombChance")->addData(smartBombChance - temp->getComponent("SmartBombChanceIncrement")->getDataInt().at(0));

				temp->getComponent("SetTargets")->deleteData();
				temp->getComponent("SetTargets")->addData(false);

				temp->getComponent("TargetOne")->deleteData();
				temp->getComponent("TargetOne")->addData(0);
				temp->getComponent("TargetTwo")->deleteData();
				temp->getComponent("TargetTwo")->addData(0);
				temp->getComponent("TargetThree")->deleteData();
				temp->getComponent("TargetThree")->addData(0);


				//Reset enemy missiles.
				for (int i = 0; i < temp->getComponent("TotalMissileCount")->getDataInt().at(0); i++)
				{
					Entity *missile = temp->getComponent("MissilesHeld")->getDataEntity().at(i);
					missile->getComponent("Life")->deleteData();
					missile->getComponent("Life")->addData(true);
					missile->getComponent("ExplosionPhase")->deleteData();
					missile->getComponent("ExplosionPhase")->addData(0);
					missile->getComponent("ExplosionRadius")->deleteData();
					missile->getComponent("ExplosionRadius")->addData(0);
					missile->getComponent("Slope")->deleteData();
					missile->getComponent("Slope")->addData(0);
					missile->getComponent("Fired")->deleteData();
					missile->getComponent("Fired")->addData(false);
					missile->getComponent("Draw")->deleteData();
					missile->getComponent("Draw")->addData(false);
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
					missile->getComponent("IsSmart")->deleteData();
					missile->getComponent("IsSmart")->addData(false);
					missile->getComponent("ShotDown")->deleteData();
					missile->getComponent("ShotDown")->addData(false);

					missile->getComponent("Sprite")->deleteData();
					sf::Sprite *s = new sf::Sprite;
					sf::Texture *t = new sf::Texture;
					if (!t->loadFromFile("missile-transit-enemy.png"))
						std::cout << "Failed to load missile-transit-enemy.png" << std::endl;
					s->setTexture(*t, true);

					missile->getComponent("Sprite")->addData(s);
					assetManager->add(t);

					sf::RectangleShape *r = missile->getComponent("RectangleShape")->getDataRectangleShape().at(0);
					r->setSize(sf::Vector2f(0, 2));

					int oldVelocity = missile->getComponent("Velocity")->getDataDouble().at(0);
					missile->getComponent("Velocity")->deleteData();
					missile->getComponent("Velocity")->addData(abs(oldVelocity) * 2);
					missile->getComponent("Velocity")->addData(1);
					missile->getComponent("Velocity")->addData(1);
				}

				for (int i = 0; i < 3; i++)
				{
					base[i]->getComponent("CurrentMissileCount")->deleteData();
					base[i]->getComponent("CurrentMissileCount")->addData(base[i]->getComponent("TotalMissileCount")->getDataInt().at(0));
					base[i]->getComponent("Life")->deleteData();
					base[i]->getComponent("Life")->addData(true);
					base[i]->getComponent("Text")->getDataText().at(0)->setString("");

					for (int j = 0; j < base[i]->getComponent("TotalMissileCount")->getDataInt().at(0); j++)
					{
						Entity *missile = base[i]->getComponent("MissilesHeld")->getDataEntity().at(j);
						missile->getComponent("Life")->deleteData();
						missile->getComponent("Life")->addData(true);
						missile->getComponent("ExplosionPhase")->deleteData();
						missile->getComponent("ExplosionPhase")->addData(0);
						missile->getComponent("ExplosionRadius")->deleteData();
						missile->getComponent("ExplosionRadius")->addData(0);
						missile->getComponent("Slope")->deleteData();
						missile->getComponent("Slope")->addData(0);
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

						missile->getComponent("CurrentPosition")->deleteData();
						missile->getComponent("CurrentPosition")->addData(missile->getComponent("StartingPosition")->getDataDouble().at(0));
						missile->getComponent("CurrentPosition")->addData(missile->getComponent("StartingPosition")->getDataDouble().at(1));

						missile->getComponent("Sprite")->deleteData();
						sf::Sprite *s = new sf::Sprite;
						s->setPosition(missile->getComponent("SpriteStartPosition")->getDataDouble().at(0), missile->getComponent("SpriteStartPosition")->getDataDouble().at(1));

						sf::Texture *texture = new sf::Texture;
						if (!texture->loadFromFile("missile.png"))
							std::cout << "Failed to load missile.png" << std::endl;
						s->setTexture(*texture);

						missile->getComponent("Sprite")->addData(s);
						assetManager->add(texture);

						int oldVelocity = missile->getComponent("Velocity")->getDataDouble().at(0);
						oldVelocity = abs(oldVelocity);
						missile->getComponent("Velocity")->deleteData();
						missile->getComponent("Velocity")->addData(oldVelocity);
						missile->getComponent("Velocity")->addData(1);
						missile->getComponent("Velocity")->addData(1);

						sf::RectangleShape *r = missile->getComponent("RectangleShape")->getDataRectangleShape().at(0);
						r->setSize(sf::Vector2f(1, 2));
					}
				}

				//Reset Planes
				Entity *planes[3] {systemManager->getMaterial("Plane1"), systemManager->getMaterial("Plane2"), systemManager->getMaterial("Plane3")};
				for (int i = 0; i < 3; i++)
				{
					planes[i]->getComponent("Life")->deleteData();
					planes[i]->getComponent("Life")->addData(true);
					planes[i]->getComponent("ExplosionPhase")->deleteData();
					planes[i]->getComponent("ExplosionPhase")->addData(0);
					planes[i]->getComponent("ExplosionRadius")->deleteData();
					planes[i]->getComponent("ExplosionRadius")->addData(0);
					planes[i]->getComponent("Draw")->deleteData();
					planes[i]->getComponent("Draw")->addData(false);
					planes[i]->getComponent("DrawSprite")->deleteData();
					planes[i]->getComponent("DrawSprite")->addData(true);
					planes[i]->getComponent("DrawCircleShape")->deleteData();
					planes[i]->getComponent("DrawCircleShape")->addData(false);
					planes[i]->getComponent("Move")->deleteData();
					planes[i]->getComponent("Move")->addData(true);
					planes[i]->getComponent("Explode")->deleteData();
					planes[i]->getComponent("Explode")->addData(false);
					planes[i]->getComponent("ShotDown")->deleteData();
					planes[i]->getComponent("ShotDown")->addData(false);
				}

				//Clear assetManager sounds
				assetManager->clearSounds();

				if (liveCities > 1)
					systemManager->getMaterial("Welcome")->getComponent("Text")->getDataText().at(0)->setString(std::to_string(liveCities) + " cities remained worth \n100 points each...\nPress any key to continue...");
				else
					systemManager->getMaterial("Welcome")->getComponent("Text")->getDataText().at(0)->setString(std::to_string(liveCities) + " city remains worth \n100 points...\nPress any key to continue...");
				return "Welcome1";
			}
		}
	}
	return "constant";
}