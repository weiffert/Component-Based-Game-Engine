#pragma once
#include <SFML/Graphics.hpp>
#include "SystemManager.h"

class MissileExploder
{
public:
  MissileExploder();
  ~MissileExploder();
  void control(sf::Window *, Entity *);
}
