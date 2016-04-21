#pragma once
#include "SystemManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Entity.h"

class MissileChecker
{
public:
  MissileChecker();
  ~MissileChecker();
  void control(sf::RenderWindow *, SystemManager *);
  bool intersection(sf::CircleShape*, sf::Vector2f); //Checks to see if a point is inside a circle
  bool intersection(Entity *, sf::CircleShape*, sf::CircleShape*); //Checks to see if two circles intersect.
  bool intersection(Entity *, sf::CircleShape*, sf::Sprite*); //Checks to see if a point is inside a rectangleshape
};
