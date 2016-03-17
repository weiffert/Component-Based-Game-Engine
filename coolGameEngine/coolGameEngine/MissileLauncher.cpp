#include "MissileLauncher.h"


MissileLauncher::MissileLauncher()
{
}


MissileLauncher::~MissileLauncher()
{
}


//Fires a missile
int MissileLauncher::fire()
{
  //Shoots missile if it has missiles left
  if (missilesLeft > 0)
  {
    //Gets starting and ending positions and sets slope
  

  
    //Decrease current missile count
  }
  
  //If it doesn't, do not fire and possibly tell the user
  
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


void MissileGuidance::setSloap()
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
