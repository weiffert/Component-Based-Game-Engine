#include "MissileLauncherAi.h"
#include <Mouse.hpp>
#include <stdlib.h> 
#include <time.h>
#include <SFML/Graphics.hpp>
#include "SystemManager.h"
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
    srand(time(NULL));
  
    targetOne = rand() % 6 + 1;
    
    targetTwo = rand() % 6 + 1;
    
    if(targetTwo == targetOne)
    {
      do
      {
        targetTwo = rand() % 6 + 1;
      }while (targetTwo == targetOne)
    }
    
    targetThree = rand() % 6 + 1;
    
    if(targetThree == targetOne)
    {
      do
      {
        targetThree = rand() % 6 + 1;
      }while(targetThree == targetOne)
    }
    
    if(targetThree == targetTwo)
    {
      do
      {
        targetThree = rand() % 6 + 1;
      }while(targetThree == targetTwo)
    }
}

void MissileLauncherAi::launchMissiles(SystemManager* systemManager, Entity *currentMissile, sf::Window & window)
{
  //Shoots missile if it has missiles left
  if (missilesLeft > 0)
  {
    srand(time(NULL));
    int missileTarget = rand() % 3 + 1;
    
    //Delete data for exploding position and starting position for missile
    currentMissile->getComponent("StartingPosition")->deleteData();
    currentMissile->getComponent("ExplodingPosition")->deleteData();
    
  
    if(missileTarget != 1)
    {
      //Push back new values with starting and ending positions
      if(targetOne == 1 || targetTwo == 1 || targetThree == 1)
      {
       //set position to the first city
       currentMissile->getComponent("ExplodingPosition")->addData(40); //y for Base1
       currentMissile->getComponent("ExplodingPosition")->addData(150);
      }
    
      else if(targetOne == 2 || targetTwo == 2 || targetThree == 2)
      {
        //set position to the second city
        currentMissile->getComponent("ExplodingPosition")->addData(40); //y for Base1
       currentMissile->getComponent("ExplodingPosition")->addData(180);
      }
    
      else if(targetOne == 3 || targetTwo == 3 || targetThree == 3)
      {
        //set position to the third city
        currentMissile->getComponent("ExplodingPosition")->addData(40); //y for Base1
       currentMissile->getComponent("ExplodingPosition")->addData(210);
      }
    
      else if(targetOne == 4 || targetTwo == 4 || targetThree == 4)
      {
       //set position to the fourth city
       currentMissile->getComponent("ExplodingPosition")->addData(40); //y for Base1
       currentMissile->getComponent("ExplodingPosition")->addData(270);
      }
    
      else if(targetOne == 5 || targetTwo == 5 || targetThree == 5)
      {
        //set position to the fifth city
       currentMissile->getComponent("ExplodingPosition")->addData(40); //y for Base1
       currentMissile->getComponent("ExplodingPosition")->addData(300);
      }
    
      else if(targetOne == 6 || targetTwo == 6 || targetThree == 6)
      {
        //set position to the sixth city
       currentMissile->getComponent("ExplodingPosition")->addData(40); //y for Base1
       currentMissile->getComponent("ExplodingPosition")->addData(330);
      }
    }
    else
    {
      int x = rand() % 3 + 1;
      
      if(x == 1)
      {
         currentMissile->getComponent("ExplodingPosition")->addData(80); //y for Base1
         currentMissile->getComponent("ExplodingPosition")->addData(120); //x for Base1
      }
      else if(x == 2)
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

void MissileLauncherAi::setSloap(int pathX, int pathY)
{
  double speedX;
  
  speedX = double(pathX) / double(pathY);
  
  return speedX;
}


