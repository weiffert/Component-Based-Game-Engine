#include "MissileLauncher.h"

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "MissileExploder.h"
#include "SystemManager.h"
#include "Property.h"
#include "Entity.h"


MissileLauncher::MissileLauncher()
{
}


MissileLauncher::~MissileLauncher()
{
}


//Fires a missile
int MissileLauncher::fire(Entity *currentMissile, Entity *currentBase, sf::RenderWindow *window, SystemManager *systemManager )
{
  
  //Shoots missile if it has missiles left
  if (missilesLeft > 0)
  {
    //Delete data for exploding position and starting position for missile
    currentMissile->getComponent("StartingPosition")->deleteData();
    currentMissile->getComponent("ExplodingPosition")->deleteData();
    
    //Push back new values with starting and ending positions, Base1 will start at 1/4 of the screen
    if(currentBase->getId() == "Base1")
    {
      currentMissile->getComponent("StartingPosition")->addData(80); //y for Base1
      currentMissile->getComponent("StartingPosition")->addData(120); //x for Base1
      //Set current position to above values
    }
    
    else if(currentBase->getId() == "Base2")
    {
      currentMissile->getComponent("StartingPosition")->addData(80); //y for Base2
	  currentMissile->getComponent("StartingPosition")->addData(240); //x for Base2
      //Set current position to above values
    }
    
    else if(currentBase->getId() == "Base3")
    {
      currentMissile->getComponent("StartingPosition")->addData(80); //y for Base3
      currentMissile->getComponent("StartingPosition")->addData(360); //x for Base3
      //Set current position to above values
    }
    
    currentMissile->getComponent("ExplodingPosition")->addData(sf::Mouse::getPosition(*window).y);
    currentMissile->getComponent("ExplodingPosition")->addData(sf::Mouse::getPosition(*window).x);
    
    //Sets slope (Which is x/y)
    currentMissile->getComponent("Slope")->deleteData();
    
    int changeX = currentMissile->getComponent("ExplodingPosition")->getDataInt().at(0)- 
    currentMissile->getComponent("StartingPosition")->getDataInt().at(0);
    
    int changeY = currentMissile->getComponent("ExplodingPosition")->getDataInt().at(1)- 
    currentMissile->getComponent("StartingPosition")->getDataInt().at(1);
    
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


double MissileLauncher::setSlope(int pathX, int pathY)
{
  double speedX;
  
  speedX = double(pathX) / double(pathY);
  
  return speedX;
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
	std::vector<Entity*> bases;
	bases.push_back(Base1);
	bases.push_back(Base2);
	bases.push_back(Base3);

	//Goes through all the missiles for the three bases
	for (int base = 1; base < 4; base++)
	{
		for (int i = 0; i < 10; i++)
		{
			std::vector<Entity *> missiles = bases.at(base)->getComponent("MissilesHeld")->getDataEntity();
			if (missiles.at(i)->getComponent("Fired")->getDataBool().at(0))
			{
				slope = missiles.at(i)->getComponent("Slope")->getDataDouble().at(0);
				missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) += slope;
				missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) -= 1;
				sf::Sprite *sprite = missiles.at(i)->getComponent("Sprite")->getDataSprite().at(0);
				sprite->move(slope, -1);
				//If the current Missile is positioned on its explosion point, (give an error of .1)

				//Check x values
				if (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) - .1 <=
					missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0) &&
					missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(0) + .1 >=
					missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(0))
				{
					//check y values
					if (missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) - .1 <=
						missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1) &&
						missiles.at(i)->getComponent("ExplodingPosition")->getDataDouble().at(1) + .1 >=
						missiles.at(i)->getComponent("CurrentPosition")->getDataDouble().at(1))
					{
						//Make the missile explode
						MissileExploder exploder;
						exploder.control(window, missiles.at(i));
						missiles.at(i)->getComponent("Life")->deleteData();
						missiles.at(i)->getComponent("Life")->addData(false);
					}
				}
			}
		}
	}
}