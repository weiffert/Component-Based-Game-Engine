#pragma once
class MissileLauncher
{
public:
	MissileLauncher();
	~MissileLauncher();
	int fire();	//Returns 0 if it fails to launch, 1 if it successfully launches
	void setMissilesLeft(int);
	void setTotalMissiles(int);
	int getMissilesLeft();
	int getTotalMissiles();
	void setSloap();
	sf::Vector2f getSloap();
	void update();
private:
	int missilesLeft;
	int totalMissiles;
	int pathX, pathY;
	sf::Vector2f sloap;
	std::vector<Missile*> activeMissiles;
};
