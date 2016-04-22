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


MissileLauncher::MissileLauncher( SystemManager * s, AssetManager * a)
{
	systemManager = s;
	assetManager = a;
}


MissileLauncher::~MissileLauncher()
{
}


//Fires a missile
int MissileLauncher::fire(Entity *currentMissile, Entity *currentBase, sf::RenderWindow *window, SystemManager *systemManager, AssetManager *assetManager)
{
	//double angle;

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
				currentMissile->getComponent("Slope")->addData(changeY / changeX);
			}

			Property*vel = currentMissile->getComponent("Velocity");
			double velX = vel->getDataDouble().at(1);
			double curX = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0);
			double expX = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0);
			double velY = vel->getDataDouble().at(2);
			double curY = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1);
			double expY = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1);
			double y = currentMissile->getComponent("CurrentPosition")->getDataDouble().at(1) - currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1);
			double x = currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0) - currentMissile->getComponent("CurrentPosition")->getDataDouble().at(0);
			
			if (y >= 0)
			{
				if (x < 0/*sqrt(pow(expX - curX - velX, 2) + pow(curY - expY - velY, 2)) > sqrt(pow(expX - curX + velX, 2) + pow(curY - expY + velY, 2))*/)
				{
					double temp = currentMissile->getComponent("Velocity")->getDataDouble().at(0);
					temp *= -1;
					vel->deleteData();
					vel->addData(temp);
					vel->addData(velX);
					vel->addData(velY);
				}

				sf::RectangleShape *temp;
				if (currentMissile->hasComponent("Sprite") && currentMissile->hasComponent("Draw") && currentMissile->hasComponent("Fired"))
				{
					if (currentMissile->getComponent("Draw")->getDataBool().at(0) && !currentMissile->getComponent("Fired")->getDataBool().at(0))
					{
						sf::Sprite *s = currentMissile->getComponent("Sprite")->getDataSprite().at(0);
						sf::RectangleShape *r = currentMissile->getComponent("RectangleShape")->getDataRectangleShape().at(0);

						r->setFillColor(*(currentMissile->getComponent("ColorFriend")->getDataColor().at(0)));
						r->setOutlineColor(*(currentMissile->getComponent("ColorFriend")->getDataColor().at(0)));

						sf::Texture *t = new sf::Texture;
						if (!t->loadFromFile("missile-transit-clear.png"))
							std::cout << "Failed to open missile-transit-clear.png" << std::endl;
						s->setTexture(*t, true);
						s->setColor(*(currentMissile->getComponent("ColorFriend")->getDataColor().at(0)));
						s->setOrigin(s->getLocalBounds().width, s->getLocalBounds().height);
					}
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

				if (currentMissile->hasComponent("DrawRectangleShape"))
				{
					currentMissile->getComponent("DrawRectangleShape")->deleteData();
					currentMissile->getComponent("DrawRectangleShape")->addData(true);
				}

				sf::Sprite *s = new sf::Sprite();
				sf::Texture *t = new sf::Texture();
				if (!t->loadFromFile("location.png"))
					std::cout << "Failed to load location.png" << std::endl;
				s->setTexture(*t);
				assetManager->add(t);

				s->setOrigin(s->getLocalBounds().width / 2, s->getLocalBounds().height / 2);
				s->setPosition(currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(0), currentMissile->getComponent("ExplodingPosition")->getDataDouble().at(1));
				currentMissile->getComponent("Sprite")->addData(s);

				return 1;
			}
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
	double length;
	sf::Vector2f rectLength;
	sf::RectangleShape *temp = nullptr;
	//sf::Vertex line[2];

	std::vector<Entity*> bases;
	bases.push_back(Base1);
	bases.push_back(Base2);
	bases.push_back(Base3);

	//Goes through all the missiles for the three bases
	for (int base = 0; base < 3; base++)
	{
		int increment = 10;
		std::vector<Entity *> missiles = bases.at(base)->getComponent("MissilesHeld")->getDataEntity();
		for (int i = 0; i < 10; i++)
		{
			if (missiles.at(i)->getComponent("Fired")->getDataBool().at(0))
			{
				increment--;
				if (missiles.at(i)->getComponent("Life")->getDataBool().at(0))
				{
					if (missiles.at(i)->hasComponent("Slope"))
						slope = missiles.at(i)->getComponent("Slope")->getDataDouble().at(0);
					if (missiles.at(i)->hasComponent("CurrentPosition") && missiles.at(i)->hasComponent("StartingPosition") && missiles.at(i)->hasComponent("Velocity"))
					{
						double theta = atan((missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) - missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1)) / (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) - missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0)));
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
					
						//Update the chem trails, set the chem trail length to the velocity
						double curX = missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0);
						double staX = missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(0);
						double curY = missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1);
						double staY = missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(1);
			
						length = sqrt(pow(staX - curX, 2) + pow(staY - curY, 2));
						temp = missiles.at(i)->getComponent("RectangleShape")->getDataRectangleShape().at(0);
						rectLength = temp->getSize();
						rectLength.x = length;
						temp->setSize(rectLength);
						if (missiles.at(i)->getComponent("Velocity")->getDataDouble().at(0) < 0)
							temp->setRotation(-1 * theta * 180 / 3.141592654 + 180);
						else
							temp->setRotation(-1 * theta * 180 / 3.141592654);
						temp->setPosition(missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(0), missiles.at(i)->getComponent("StartingPosition")->getDataDouble().at(1));
						temp->setOrigin(0, temp->getLocalBounds().height);
					}

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
							missiles.at(i)->getComponent("Life")->deleteData();
							missiles.at(i)->getComponent("Life")->addData(false);
							missiles.at(i)->getComponent("DrawSprite")->deleteData();
							missiles.at(i)->getComponent("DrawSprite")->addData(false);
							missiles.at(i)->getComponent("DrawCircleShape")->deleteData();
							missiles.at(i)->getComponent("DrawCircleShape")->addData(true);
							missiles.at(i)->getComponent("DrawRectangleShape")->deleteData();
							missiles.at(i)->getComponent("DrawRectangleShape")->addData(false);
							missiles.at(i)->getComponent("Move")->deleteData();
							missiles.at(i)->getComponent("Move")->addData(false);
							missiles.at(i)->getComponent("Explode")->deleteData();
							missiles.at(i)->getComponent("Explode")->addData(true);

							//Explosion sound
							sf::Sound * sound = new sf::Sound;
							sound->setBuffer(*missiles.at(i)->getComponent("SoundMissileExplosion")->getDataSoundBuffer().at(0));
							assetManager->add(sound);
							sound->play();

							sf::CircleShape *c = missiles.at(i)->getComponent("CircleShape")->getDataCircleShape().at(0);
							c->setPosition(missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0), missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1));
								MissileExploder exploder;
							exploder.control(systemManager, window, missiles.at(i));
						}
					}
				}
			}
			if (increment <= 3)
			{
				sf::Text *t = bases.at(base)->getComponent("Text")->getDataText().at(0);
				t->setString("Low");

				//Play warning sound if we want to.
			}
			if (increment <= 0)
			{
				sf::Text *t = bases.at(base)->getComponent("Text")->getDataText().at(0);
				t->setString("Out");
			}
			if (missiles.at(i)->hasComponent("Explode"))
			{
				if (missiles.at(i)->getComponent("Explode")->getDataBool().at(0))
				{
					MissileExploder exploder;
					exploder.control(systemManager, window, missiles.at(i));
				}
			}
		}
	}
}
