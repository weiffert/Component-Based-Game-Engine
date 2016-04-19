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

int getTotalScore();

int getStockedCities();


};



