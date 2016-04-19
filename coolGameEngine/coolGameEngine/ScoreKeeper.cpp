#include "stdafx.h"

#include "ScoreKeeper.h"

#include "SystemManger.h"




ScoreKeeper::ScoreKeeper()
{
  totalScore = 0;
  recentScore = 0;
  stockedCities = 0;
}

ScoreKeeper::~ScoreKeeper()
{

}

void ScoreKeeper::clearScore()
{
  totalScore = 0;
  recentScore = 0;
  stockedCities = 0;
}

void ScoreKeeper::levelEnd()
{
  if(systemManager->getMaterial("City1")->getComponent("Life")->getDataBool() == false)
  {
      totalScore += 
  }

  
}

void ScoreKeeper::buildCity(SystemManger* systemManager)
{
   if(stockedCities > 0)
   {
     if(systemManager->getMaterial("City1")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City1")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City1")->getComponent("Life")->addData(true);
     }
     else if(systemManager->getMaterial("City2")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City2")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City2")->getComponent("Life")->addData(true);
     }
     else if(systemManager->getMaterial("City3")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City3")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City3")->getComponent("Life")->addData(true);
     }
     else if(systemManager->getMaterial("City4")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City4")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City4")->getComponent("Life")->addData(true);
     }
     else if(systemManager->getMaterial("City5")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City5")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City5")->getComponent("Life")->addData(true);
     }
     else if(systemManager->getMaterial("City6")->getComponent("Life")->getDataBool() == false)
     {
      systemManager->getMaterial("City6")->getComponent("Life")->deleteData();
      systemManager->getMaterial("City6")->getComponent("Life")->addData(true);
     }

   }

}

void ScoreKeeper::increaseScore(int points)
{
  totalScore += points;
  recentScore += points;

  if(recentScore >= 10000)
  {
   stockedCities += 1;
   recentScore = 0;
  }
}
