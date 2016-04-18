#pragma once

#include "stdafx.h"

class ScoreKeeper;
{

private:

int recentScore;



public:

ScoreKeeper();

~ScoreKeeper();

void buildCity();

void increaseScore(int);

void checkForCity();

int totalScore;

int stockedCities;


};



