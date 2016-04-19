#include "Plane.h"

#include <stdlib.h> 
#include <time.h>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "Property.h"
#include "Entity.h"

#include "MissileLauncherAi.h"
#include "MissileExploder.h"


Plane::Plane()
{
  totalMissiles = 10;
  missilesLeft = 10;

}


Plane::Plane(int totalMis, int currMis, int height , SystemManager * systemManager)
{
  totalMissiles = totalMis;
  missilesLeft = currMis;
  
  systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->deleteData();
  systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->addData(height);
  systemManager->getMaterial("Plane")->getComponent("CurrentPosition")->addData(0);
}


Plane::~Plane()
{

}


int Plane::launchMissiles(Entity *currentMissile, sf::RenderWindow *window, SystemManager * systemManager)
{
	//Shoots missile if it has missiles left

	if (missilesLeft > 0)
	{
		int missileTarget = rand() % 3 + 1;

		//Delete data for exploding position and starting position for missile
		if (currentMissile->hasComponent("StartingPosition"))
			currentMissile->getComponent("StartingPosition")->deleteData();
		if (currentMissile->hasComponent("ExplodingPosition"))
			currentMissile->getComponent("ExplodingPosition")->deleteData();


		if (missileTarget != 1)
		{
			int currentTarget = rand() % 3 + 1;
			
			if( currentTarget == 1)
			{
				currentTarget = targetOne;
			}
			else if (currentTarget == 2)
			{
				currentTarget = targetTwo;
			}
			else
			{
				currentTarget = targetThree;
			}
			
			//Push back new values with starting and ending positions
			if (currentTarget == 1)
			{
				//set position to the first city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(150);
			}

			else if (currentTarget == 2)
			{
				//set position to the second city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(180);
			}

			else if (currentTarget == 3)
			{
				//set position to the third city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(210);
			}

			else if (currentTarget == 4)
			{
				//set position to the fourth city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(270);
			}

			else if (currentTarget == 5)
			{
				//set position to the fifth city
				currentMissile->getComponent("ExplodingPosition")->addData(40); 
				currentMissile->getComponent("ExplodingPosition")->addData(300);
			}

			else if (currentTarget == 6)
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


void Plane::update(sf::RenderWindow *window,  SystemManager * systemManager)
{
	double slope;
	double temp1, temp2;
	double length;
	int planeNumber = 1;
	sf::Vector2f rectLength;
	sf::RectangleShape *temp = nullptr;
	sf::Sprite * plane = nullptr;
	Entity * currentPlane = nullptr;
	MissileLauncherAi missileLauncherAi;
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

			//Goes through all the missiles for the current plane and move them
			for (int i = 0; i < 10; i++)
			{
				if (missiles.at(i)->hasComponent("Fired"))
				{
					if (missiles.at(i)->getComponent("Fired")->getDataBool().at(0))
					{
						if (missiles.at(i)->getComponent("Life")->getDataBool().at(0))
						{
							if (missiles.at(i)->hasComponent("Slope"))
								slope = missiles.at(i)->getComponent("Slope")->getDataDouble().at(0);
							if (missiles.at(i)->hasComponent("CurrentPosition") && missiles.at(i)->hasComponent("StartingPosition") && missiles.at(i)->hasComponent("Velocity"))
							{
								double theta = atan((missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) - missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1)) / (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) - missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0)));
								theta *= -1;
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

									sf::CircleShape *c = missiles.at(i)->getComponent("CircleShape")->getDataCircleShape().at(0);
									c->setPosition(missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0), missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1));
									MissileExploder exploder;
									exploder.control(systemManager, window, missiles.at(i));
									//Do whatever to what was exploded.
									std::string targetString = missiles.at(i)->getComponent("Target")->getDataString().at(0);
									Entity *target = systemManager->getMaterial(targetString);
									if (target->getComponent("Life")->getDataBool().at(0))
									{
										target->getComponent("Life")->deleteData();
										target->getComponent("Life")->addData(false);
										target->getComponent("Draw")->deleteData();
										target->getComponent("Draw")->addData(false);
										target->getComponent("DrawSprite")->deleteData();
										target->getComponent("DrawSprite")->addData(false);

										if (targetString.find("Base") != std::string::npos)
										{
											for (int i = 0; i < target->getComponent("CurrentMissileCount")->getDataInt().at(0); i++)
											{
												Entity *missile = target->getComponent("MissilesHeld")->getDataEntity().at(i);
												missile->getComponent("Life")->deleteData();
												missile->getComponent("Life")->addData(false);
												missile->getComponent("Draw")->deleteData();
												missile->getComponent("Draw")->addData(false);
											}
										}
									}
								}
							}

							//Checks to fire missiles (will add firing functionality here)


							//checks if it is the last missile
							if (i != 1)
							{
								//checks if missile already split and is high enough
								if (missiles.at(i)->getComponent("Split")->getDataBool().at(0) == false && missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) < 340)
								{
									//random chance to not split
									if (rand() % systemManager->getMaterial("MissileLauncherAi")->getComponent("SplitChance")->getDataInt().at(0) == 0)
									{
										int decrement = 29;
										bool found = false;
										Entity *missile = nullptr;
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
											missiles.at(i)->getComponent("Split")->deleteData();
											missiles.at(i)->getComponent("Split")->addData(true);

											missile->getComponent("SplitFired")->deleteData();
											missile->getComponent("SplitFired")->addData(true);

											missile->getComponent("StartingPosition")->deleteData();
											missile->getComponent("StartingPosition")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0));
											missile->getComponent("StartingPosition")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));

											missile->getComponent("CurrentPosition")->deleteData();
											missile->getComponent("CurrentPosition")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0));
											missile->getComponent("CurrentPosition")->addData(missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1));

											missileLauncherAi.launchMissiles(missile, window);
										}
									}

								}
							}
						}
						if (missiles.at(i)->hasComponent("Explode"))
						{
							if (missiles.at(i)->getComponent("Explode")->getDataBool().at(0))
							{

								//Make the missile explode
								//missiles.at(i)->getComponent("Life")->deleteData();
								//missiles.at(i)->getComponent("Life")->addData(false);
								MissileExploder exploder;
								exploder.control(systemManager, window, missiles.at(i));
							}
						}
					}
				}
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
				this->launchPlane(window, systemManager, 1);
			else if (systemManager->getMaterial("Plane2")->getComponent("Life")->getDataBool().at(0))
				this->launchPlane(window, systemManager, 2);
			else if (systemManager->getMaterial("Plane3")->getComponent("Life")->getDataBool().at(0))
				this->launchPlane(window, systemManager, 3);
		}
	}
}


void Plane::launchPlane(sf::RenderWindow * window, SystemManager * systemManager, int planeNumber)
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

	delete direction;
}