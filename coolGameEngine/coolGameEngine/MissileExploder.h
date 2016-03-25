#pragma once
#include <SFML/Graphics.hpp>
class MissileExploder
{
public:
  MissileExploder();
  ~MissileExploder();
  void control(sf::Window&, Entity *);
private:
  sf::CircleShape explosion;
  sf::Transform wave;
  const double MAX_RADIUS = 11;
}
