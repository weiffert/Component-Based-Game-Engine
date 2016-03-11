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

