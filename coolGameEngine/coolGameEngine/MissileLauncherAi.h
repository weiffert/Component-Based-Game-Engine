#pragma once

#include <vector>

#inlcude "SFML/Graphics.hpp"

class MissileLauncherAi
{
public:

std::vector<EnemyMissiles> activeMissiles;
int currentMissile, totalMissile, pathX, pathY;
sf::Vector2f sloap;

private:

MissileLauncherAi();

MissileLauncherAi(int, int);
void selectBase();
void setSloap();
sf::Vector2f getSloap();
void changeTotal(int);
void changeCurrent(int);
void launchMissiles();
bool checkForMissiles();

~MissleLauncherAi();

