#pragma once

#include <vector>

#inlcude "SFML/Graphics.hpp"

class MissileLauncherAi
{
public:

std::vector<EnemyMissiles> activeMissiles;
int currentMissile, totalMissile;

private:

MissileLauncherAi();

MissileLauncherAi(int, int);

void changeTotal(int);
void changeCurrent(int);
void launchMissiles();
bool checkForMissiles();

~MissleLauncherAi();

