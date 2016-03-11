#include <time.h>
#include <stdlib.h>
#include <vector>;
#include "MissileLauncherAi.h"
#include "SFML/Graphics.hpp"

int x;
std::vector<EnemyMissile*> activeMissiles; 


srand(time(NULL));

if(activeMissiles.empty() == true)
{

  if(CurrentMissileCount >= 2)
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
  else if(CurrentMissileCount == 1)
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
    currentMissile--;
  }
  
  
  do
  {
    for(x = 0; x < activeMissiles.size(); x++)
    {
      sf::FloatRect missileBox = activeMissile.at(x).getGlobalBounds()
      if(missileBox.intersects(baseBox) | missileBox.intersects(boomBox))
      {
        activeMissile.erase(x);
      }
    }
  }while(ativeMissile.empty() == false);


}




























