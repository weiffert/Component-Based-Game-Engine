#include "MissileExploder.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "SystemManager.h"
#include "Property.h"
#include "Entity.h"
#include "ScoreKeeper.h"


MissileExploder::MissileExploder()
{
}


MissileExploder::~MissileExploder()
{
}


//This function currently explodes a missile, and creates a circle explosion
//This function is called from MissileLauncher
void MissileExploder::control(SystemManager *systemManager, sf::RenderWindow * window, Entity *missile)
{
	double rate;
	rate = 2;
	double tempRadius;
	if (missile->getComponent("Explode")->getDataBool().at(0)) //Makes sure the explosion didn't already happen
	{
		//If it doesn't already have an explosion, create one (property "ExplosionPhase" is 0)
		if (missile->getComponent("ExplosionPhase")->getDataInt().at(0) == 0)
		{
			missile->getComponent("ExplosionPhase")->deleteData();
			missile->getComponent("ExplosionPhase")->addData(1);

			//Play explosion sound. This has been moved to outside of missile exploder
			//if (missile->hasComponent("SoundMissileExplosion"))
			//{
			//	sf::Sound s;
			//	s.setBuffer(*(missile->getComponent("SoundMissileExplosion")->getDataSoundBuffer().at(0)));
			//	s.play();
			//}

			//Points handling.
			if (missile->hasComponent("ShotDown"))
			{
				if (missile->getComponent("ShotDown")->getDataBool().at(0))
				{
					ScoreKeeper scoreKeeper;
					//If its a missile.
					if (missile->getId().find("Plane") == std::string::npos)
					{
						if (missile->getId().find("Enemy") != std::string::npos)
						{
							if (missile->hasComponent("IsSmart"))
							{
								if (missile->getComponent("IsSmart")->getDataBool().at(0))
								{
									scoreKeeper.increaseScore(125, systemManager->getMaterial("Player"));
								}
								else
								{
									scoreKeeper.increaseScore(25, systemManager->getMaterial("Player"));
								}
							}
							else
							{
								scoreKeeper.increaseScore(25, systemManager->getMaterial("Player"));
							}
						}
					}
					//Its a plane
					else
					{
						scoreKeeper.increaseScore(50, systemManager->getMaterial("Player"));
					}
				}
			}

			//Add missile to exploding missiles for missileChecker.
			systemManager->getComponent("ExplodingMissiles")->addData(missile);
		}

		//Check radius
		if (missile->getComponent("ExplosionRadius")->getDataDouble().at(0) >= 30)
		{
			missile->getComponent("ExplosionPhase")->deleteData();
			missile->getComponent("ExplosionPhase")->addData(-1);
		}

		//Check to see if the explosion disappears
		if (missile->getComponent("ExplosionRadius")->getDataDouble().at(0) < 0)
		{
			missile->getComponent("ExplosionRadius")->deleteData();
			missile->getComponent("ExplosionRadius")->addData(0);
			missile->getComponent("ExplosionPhase")->deleteData();
			missile->getComponent("ExplosionPhase")->addData(-2);
			missile->getComponent("Explode")->deleteData();
			missile->getComponent("Explode")->addData(false);
			missile->getComponent("DrawCircleShape")->deleteData();
			missile->getComponent("DrawCircleShape")->addData(false);
			systemManager->getComponent("ExplodingMissiles")->deleteDataPosition(missile->getId());
		}

		tempRadius = missile->getComponent("ExplosionRadius")->getDataDouble().at(0);
		tempRadius += rate * missile->getComponent("ExplosionPhase")->getDataInt().at(0);
		missile->getComponent("ExplosionRadius")->deleteData();
		missile->getComponent("ExplosionRadius")->addData(tempRadius);
		sf::CircleShape *c = missile->getComponent("CircleShape")->getDataCircleShape().at(0);
		c->setRadius(tempRadius);
		c->setOrigin(c->getRadius(), c->getRadius());
	}
}
