#pragma once
class MissileLauncher
{
public:
	MissileLauncher();
	~MissileLauncher();
	void fire();
	void setMissilesLeft(int);
	void setTotalMissiles(int);
	int getMissilesLeft();
	int getTotalMissiles();
	void setSloap();
	sf::Vector2f getSloap();
private:
	int missilesLeft;
	int totalMissiles;
	int pathX, pathY;
	sf::Vector2f sloap;
};
