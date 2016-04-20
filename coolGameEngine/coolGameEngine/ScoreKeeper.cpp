#include "stdafx.h"
#include "ScoreKeeper.h"

#include "SFML/Graphics.hpp"

#include "SystemManager.h"
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

void ScoreKeeper::buildCities(SystemManager* systemManager)
{
	while (stockedCities > 0)
	{
		if (systemManager->getMaterial("City1")->getComponent("Life")->getDataBool().at(0) == false)
		{
			systemManager->getMaterial("City1")->getComponent("Life")->deleteData();
			systemManager->getMaterial("City1")->getComponent("Life")->addData(true);
			stockedCities -= 1;
		}
		else if (systemManager->getMaterial("City2")->getComponent("Life")->getDataBool().at(0) == false)
		{
			systemManager->getMaterial("City2")->getComponent("Life")->deleteData();
			systemManager->getMaterial("City2")->getComponent("Life")->addData(true);
			stockedCities -= 1;
		}
		else if (systemManager->getMaterial("City3")->getComponent("Life")->getDataBool().at(0) == false)
		{
			systemManager->getMaterial("City3")->getComponent("Life")->deleteData();
			systemManager->getMaterial("City3")->getComponent("Life")->addData(true);
			stockedCities -= 1;
		}
		else if (systemManager->getMaterial("City4")->getComponent("Life")->getDataBool().at(0) == false)
		{
			systemManager->getMaterial("City4")->getComponent("Life")->deleteData();
			systemManager->getMaterial("City4")->getComponent("Life")->addData(true);
			stockedCities -= 1;
		}
		else if (systemManager->getMaterial("City5")->getComponent("Life")->getDataBool().at(0) == false)
		{
			systemManager->getMaterial("City5")->getComponent("Life")->deleteData();
			systemManager->getMaterial("City5")->getComponent("Life")->addData(true);
			stockedCities -= 1;
		}
		else if (systemManager->getMaterial("City6")->getComponent("Life")->getDataBool().at(0) == false)
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
	int multiplyer = player->getComponent("ScoreMultiplyer")->getDataInt().at(0);
	totalScore += (points * multiplyer);

	player->getComponent("Points")->deleteData();
	player->getComponent("Points")->addData(totalScore);

	recentScore += (points * multiplyer);

	if (recentScore >= 10000)
	{
		stockedCities += (recentScore / 10000);
		recentScore = 0;
	}
}


void ScoreKeeper::printScore(Entity *player, sf::RenderWindow *window)
{
  font.loadFromFile("Square.ttf");
  
  int totalScore = player->getComponent("Points")->getDataInt().at(0);
  
  score.setFont(font);
  score.setString(std::to_string(totalScore));
  score.setCharacterSize(20);
  score.setPosition(240, 30);

  window->draw(score);
}

