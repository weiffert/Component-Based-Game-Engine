#pragma once

#include "stdafx.h"

class ScoreKeeper;
{

private:

int recentScore;

int totalScore;

int stockedCities;


public:

ScoreKeeper();

~ScoreKeeper();

void buildCity();

void increaseScore(int);

void clearScore();

void levelEnd();

int getTotalScore();

int getStockedCities();


};



