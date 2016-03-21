#include "MissileLauncher.h"
#include <Mouse.hpp>

MissileLauncher::MissileLauncher()
{
}


MissileLauncher::~MissileLauncher()
{
}


//Fires a missile
int MissileLauncher::fire(Entity *currentMissile, Entity *currentBase, sf::Window window)
{
  //Shoots missile if it has missiles left
  if (missilesLeft > 0)
  {
    //Delete data for exploding position and starting position for missile
    currentMissile->getProperty("StartingPosition")->deleteData();
    currentMissile->getProperty("ExplodingPosition")->deleteData();
    
    //Push back new values with starting and ending positions
    if(currentBase->getId() == "Base1")
    {
      currentMissile->getProperty("StartingPosition")->addData(); //y for Base1
      currentMissile->getProperty("StartingPosition")->addData(); //x for Base1
    }
    
    else if(currentBase->getId() == "Base2")
    {
      currentMissile->getProperty("StartingPosition")->addData(); //y for Base2
      currentMissile->getProperty("StartingPosition")->addData(); //x for Base2
    }
    
    else if(currentBase->getId() == "Base3")
    {
      currentMissile->getProperty("StartingPosition")->addData(); //y for Base3
      currentMissile->getProperty("StartingPosition")->addData(); //x for Base3
    }
    
    currentMissile->getProperty("ExplodingPosition")->addData(sf::Mouse::getPosition(window).y);
    currentMissile->getProperty("ExplodingPosition")->addData(sf::Mouse::getPosition(window).x);
    
    //Sets slope (Which is x/y)
    this->setSloap
    
    
    
    //Decrease missiles left
    
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


void MissileLauncher::setSloap(int pathX, int pathY)
{
  double speedX;
  
  speedX = double(pathX) / double(pathY);
  
  sloap = (speedX, 1);
}


sf::Vector2f MissileGuidance::getSloap()
{
  return sloap;
}


int MissileLauncher::getMissilesLeft()
{
  return missilesLeft;
}


int MissileLauncher::getTotalMissiles()
{
  return totalMissiles;
}


void MissileLauncher::update()
{
  
}
