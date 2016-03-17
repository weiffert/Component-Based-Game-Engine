#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <vector>;
#include "MissileLauncherAi.h"
#include "SFML/Graphics.hpp"


MissileLauncherAi::MissileLauncherAi()
{
  totalMissiles = 10;
  currentMissiles = 10;
}

MissileLauncherAi::MissileLauncherAi(int totalMis, int currMis)
{
  totalMissiles = totalMis;
  currentMissiles = currMis;
}

void MissileLauncherAi::launchMissiles()
{
  int x;
  srand(time(NULL));  

  if(currentMissiles >= 2)
  {
    x = rand() % 3;
  
    if( x == 2)
    {
      activeMissiles.push_back(new EnemyMissile);
      activeMissiles.push_back(new EnemyMissile);
    }
    else if( x == 1)
    {
      activeMissiles.push_back(new EnemyMissile);
    }
  }
  else if(currentMissiles == 1)
  {
    x = rand() % 2;
  
    if(x == 1)
    {
      activeMissiles.push_back(new EnemyMissile);
    }
  }
  
  for(x = 0; x < activeMissiles.size(); x++)
  {
    activeMissiles.at(x).setPosition(rand() % 1279 + 1, -5)
    currentMissiles--;
  }
}

void MissileGuidance::selectBase()
{
  srand(time(NULL));
  
  int x = rand() % 3 + 1, y;
  
  if(x == 3)
  {
    x = rand() % (base image width) + 1;
    
    pathX = (screen width) - (distance between base and right edge) - x;
    
    y = rand() % (base image height) + 1;
    
    pathY = (screen height) - (distance between base and screen bottom) - y;
  }
  else if(x == 2)
  {
     x = rand() % (base image width) + 1;
    
    pathX = (screen width) - (distance between base and right edge) - x;
    
    y = rand() % (base image height) + 1;
    
    pathY = (screen height) - (distance between base and screen bottom) - y;
  }
  else
  {
    x = rand() % (base image width) + 1;
    
    pathX = (screen width) - (distance between base and right edge) - x;
    
    y = rand() % (base image height) + 1;
    
    pathY = (screen height) - (distance between base and screen bottom) - y;
  }
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

bool MissileLauncherAi::checkForMissiles()
{
   for(int x = 0; x < activeMissiles.size(); x++)
  {
    if(activeMissiles.at(x)= nullptr)
    {
      activeMissiles.erase(x);
    }
  }
  
  if(activeMissiles.empty() = true)
  {
    return false;
  }
  else
  {
    return true;
  }
}

