#pragma once

#include "SystemManager.h"
#include "Entity.h"

class ScoreKeeper
{
  private:
  
  int recentScore;
  int stockedCities;
  
  public:
  
  ScoreKeeper();
  ~ScoreKeeper();
  
  void increaseScore(int, Entity*);
  void printScore();
  void buildCities();
  


};
