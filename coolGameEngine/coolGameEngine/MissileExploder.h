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

}
