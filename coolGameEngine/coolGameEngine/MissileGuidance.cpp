#include "stdafx.h"

#include <stdlib.h>
#include <time.h>

#include "MissileGuidance.h"


MissileGuidance::MissileGuidance()
{

}

MissileGuidance::MissileGuidance(int xCord)
{
  pathX = xCord;
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

MissileGuidance::~MissileGuidance()
{
  
}
