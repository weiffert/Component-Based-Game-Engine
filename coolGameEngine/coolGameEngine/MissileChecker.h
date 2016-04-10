#pragma once
#include "SystemManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

class MissileChecker
{
public:
  MissileChecker();
  ~MissileChecker();
  void control(sf::RenderWindow *, SystemManager *);
};
