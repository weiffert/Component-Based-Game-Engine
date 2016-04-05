#include "MissileLauncherAi.h"
#include <Mouse.hpp>
#include <SFML/Graphics.hpp>
#include "MissileExploder.h"


MissileLauncherAi::MissileLauncherAi()
{
  totalMissiles = 10;
  missilesLeft = 10;
}

MissileLauncherAi::MissileLauncherAi(int totalMis, int currMis)
{
  totalMissiles = totalMis;
  missilesLeft = currMis;
}

void MissileLauncherAi::setTargets()
{
    targetOne = rand() % 9 + 1;
    
    targetTwo = rand() % 9 + 1;
    
    if(targetTwo == targetOne)
    {
      do
      {
        targetTwo = rand() % 9 + 1;
      }while (targetTwo == targetOne)
    }
    
    targetThree = rand() % 9 + 1;
    
    if(targetThree == targetOne)
    {
      do
      {
        targetThree = rand() % 9 + 1;
      }while(targetThree == targetOne)
    }
    
    if(targetThree == targetTwo)
    {
      do
      {
        targetThree = rand() % 9 + 1;
      }while(targetThree == targetTwo)
    }
}

void MissileLauncherAi::launchMissiles(Entity *currentMissile, Entity *currentBase, sf::Window & window)
{
  //Shoots missile if it has missiles left
  if (missilesLeft > 0)
  {
    //Delete data for exploding position and starting position for missile
    currentMissile->getComponent("StartingPosition")->deleteData();
    currentMissile->getComponent("ExplodingPosition")->deleteData();
    
    
    
    
    //Push back new values with starting and ending positions
    if(targetOne == 1 || targetTwo == 1 || targetThree == 1)
    {
      currentMissile->getComponent("ExplodingPosition")->addData(); //y for Base1
      currentMissile->getComponent("ExplodingPosition")->addData(); //x for Base1
      //Set current position to above values
    }
    
    else if(targetOne == 2 || targetTwo == 2 || targetThree == 2)
    {
      //set position to the first city
    }
    
    else if(targetOne == 3 || targetTwo == 3 || targetThree == 3)
    {
      //set position to the second city
    }
    
    else if(targetOne == 4 || targetTwo == 4 || targetThree == 4)
    {
      //set position to the third city
    }
    
    else if(targetOne == 5 || targetTwo == 5 || targetThree == 5)
    {
      currentMissile->getComponent("ExplodingPosition")->addData(); //y for Base2
      currentMissile->getComponent("ExplodingPosition")->addData(); //x for Base2
      //Set current position to above values
    }
    
    else if(targetOne == 6 || targetTwo == 6 || targetThree == 6)
    {
      //set position to the fourth city
    }
    
    else if(targetOne == 7 || targetTwo == 7 || targetThree == 7)
    {
      //set position to the fifth city
    }
    
    else if(targetOne == 8 || targetTwo == 8 || targetThree == 8)
    {
      //set position to the sixth city
    }
    
    else if(targetOne == 9 || targetTwo == 9 || targetThree == 9)
    {
      currentMissile->getComponent("ExplodingPosition")->addData(); //y for Base3
      currentMissile->getComponent("ExplodingPosition")->addData(); //x for Base3
      //Set current position to above values
    }
    
    currentMissile->getComponent("StartingPosition")->(someplace off-screen);
    currentMissile->getComponent("StartingPosition")->(random x position);
    
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
}

int MissileLauncherAi::LaunchAmmount()
{
  if(missilesLeft > 2)
  {
    return rand() % 3 + 1;
  }
  else if(missilesLeft > 1)
  {
    return rand() % 2 + 1;
  }
  else if(missilesLeft == 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void MissileGuidance::setSloap(int pathX, int pathY)
{
  double speedX;
  
  speedX = double(pathX) / double(pathY);
  
  return speedX;
}


