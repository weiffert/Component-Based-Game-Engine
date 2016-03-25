#include "MissileLauncher.h"
#include <Mouse.hpp>
#include <SFML/Graphics.hpp>
#include "MissileExploder.h"

MissileLauncher::MissileLauncher()
{
}


MissileLauncher::~MissileLauncher()
{
}


//Fires a missile
int MissileLauncher::fire(Entity *currentMissile, Entity *currentBase, sf::Window & window)
{
  //Shoots missile if it has missiles left
  if (missilesLeft > 0)
  {
    //Delete data for exploding position and starting position for missile
    currentMissile->getComponent("StartingPosition")->deleteData();
    currentMissile->getComponent("ExplodingPosition")->deleteData();
    
    //Push back new values with starting and ending positions
    if(currentBase->getId() == "Base1")
    {
      currentMissile->getComponent("StartingPosition")->addData(); //y for Base1
      currentMissile->getComponent("StartingPosition")->addData(); //x for Base1
      //Set current position to above values
    }
    
    else if(currentBase->getId() == "Base2")
    {
      currentMissile->getComponent("StartingPosition")->addData(); //y for Base2
      currentMissile->getComponent("StartingPosition")->addData(); //x for Base2
      //Set current position to above values
    }
    
    else if(currentBase->getId() == "Base3")
    {
      currentMissile->getComponent("StartingPosition")->addData(); //y for Base3
      currentMissile->getComponent("StartingPosition")->addData(); //x for Base3
      //Set current position to above values
    }
    
    currentMissile->getComponent("ExplodingPosition")->addData(sf::Mouse::getPosition(window).y);
    currentMissile->getComponent("ExplodingPosition")->addData(sf::Mouse::getPosition(window).x);
    
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


sf::Vector2f MissileGuidance::getSlope()
{
  return slope;
}


int MissileLauncher::getMissilesLeft()
{
  return missilesLeft;
}


int MissileLauncher::getTotalMissiles()
{
  return totalMissiles;
}


void MissileLauncher::update(sf::Window & window, Entity * Base1, Entity * Base2, Entity * Base3)
{
  double slope;
  
  //Goes through all the missiles for Base1
  for (int i = 0; i < 10; i++)
  {
    if (Base1->getComponent("MissilesHeld1")->getDataEntity().at(i)->getComponent("Fired").at(0))
    {
    slope = Base1->getComponent("MissilesHeld1")->getDataEntity().at(i)->getComponent("Slope").at(0);
    Base1->getComponent("MissilesHeld1")->getDataEntity().at(i)->getComponent("CurrentPosition").at(0) += slope;
    Base1->getComponent("MissilesHeld1")->getDataEntity().at(i)->getComponent("CurrentPosition").at(1) -= 1;
    Base1->getComponent("MissilesHeld1")->getDataEntity().at(i)->getComponent("SpriteMissile").at(0)->move(slope, -1);
    }
  }
  
  for (int i = 0; i < 10; i++)
  {
    if (Base2->getComponent("MissilesHeld2")->getDataEntity().at(i)->getComponent("Fired").at(0))
    {
    slope = Base2->getComponent("MissilesHeld2")->getDataEntity().at(i)->getComponent("Slope").at(0);
    Base2->getComponent("MissilesHeld2")->getDataEntity().at(i)->getComponent("CurrentPosition").at(0) += slope;
    Base2->getComponent("MissilesHeld2")->getDataEntity().at(i)->getComponent("CurrentPosition").at(1) -= 1;
    Base2->getComponent("MissilesHeld2")->getDataEntity().at(i)->getComponent("SpriteMissile").at(0)->move(slope, -1);
    }
  }
  
  for (int i = 0; i < 10; i++)
  {
    if (Base3->getComponent("MissilesHeld3")->getDataEntity().at(i)->getComponent("Fired").at(0))
    {
    slope = Base3->getComponent("MissilesHeld3")->getDataEntity().at(i)->getComponent("Slope").at(0);
    Base3->getComponent("MissilesHeld3")->getDataEntity().at(i)->getComponent("CurrentPosition").at(0) += slope;
    Base3->getComponent("MissilesHeld3")->getDataEntity().at(i)->getComponent("CurrentPosition").at(1) -= 1;
    Base3->getComponent("MissilesHeld3")->getDataEntity().at(i)->getComponent("SpriteMissile").at(0)->move(slope, -1);
    }
  }
}
