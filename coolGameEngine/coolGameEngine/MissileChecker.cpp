#include "MissileChecker.h"

#include <SFML/Graphics.hpp>
#include "SystemManager.h"
MissileChecker::MissileChecker()
{
}

MissileChecker::~MissileChecker()
{
}

void MissileChecker::control(sf::RenderWindow * window, SystemManager * systemManager)
{
  //Goes through each enemy missile and determines if they should explode, if they should explode call on MissileExploder
  
}
