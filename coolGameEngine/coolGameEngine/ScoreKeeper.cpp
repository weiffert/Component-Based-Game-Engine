#include "stdafx.h"

#include "ScoreKeeper.h"
#include "SystemManger.h"
#include "Entity.h"
#include "Property.h"


ScoreKeeper::ScoreKeeper()
{
  totalScore = 0;
  recentScore = 0;
  stockedCities = 0;
}

ScoreKeeper::~ScoreKeeper()
{

}

void ScoreKeeper::buildCities(SystemManger* systemManager)
{
   while(stockedCities > 0)
   {
     if(systemManager->getMaterial("City1")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City1")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City1")->getComponent("Life")->addData(true);
      stockedCities -= 1;
     }
    else if(systemManager->getMaterial("City2")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City2")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City2")->getComponent("Life")->addData(true);
      stockedCities -= 1;
     }
    else if(systemManager->getMaterial("City3")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City3")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City3")->getComponent("Life")->addData(true);
      stockedCities -= 1;
     }
    else if(systemManager->getMaterial("City4")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City4")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City4")->getComponent("Life")->addData(true);
      stockedCities -= 1;
     }
    else if(systemManager->getMaterial("City5")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City5")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City5")->getComponent("Life")->addData(true);
      stockedCities -= 1;
     }
    else if(systemManager->getMaterial("City6")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City6")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City6")->getComponent("Life")->addData(true);
      stockedCities -= 1;
     }

   }

}

void ScoreKeeper::increaseScore(int points, Entity *player)
{
  
  int totalScore = player->getComponent("Points")->getDataInt().at(0);
  int multiplyer = player->getComponent("ScoreMultiplyer")->getDataInt().at(0)
  totalScore += (points * multiplyer);
  
  player->getComponent("Points")->deleteData();
  player->getComponent("Points")->addData(totalScore);
  
  recentScore += (points * multiplyer);

  if(recentScore >= 10000)
  {
   stockedCities += (recentScore / 10000);
   recentScore = 0;
  }
}
