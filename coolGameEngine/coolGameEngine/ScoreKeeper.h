#pragma once

#include "SFML/Graphics.hpp"

#include "SystemManager.h"
#include "Entity.h"

class ScoreKeeper
{
  private:
  
  int recentScore;
  int stockedCities;
  sf::Font font;
  sf::Text score;
  
  public:
  
  ScoreKeeper();
  ~ScoreKeeper();
  
  void increaseScore(int, Entity*);
  void printScore(Entity*, RenderWindow*);
  void buildCities();
  


};
