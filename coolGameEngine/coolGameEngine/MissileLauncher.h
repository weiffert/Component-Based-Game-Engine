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
	void setSloap(int, int);
	sf::Vector2f getSloap();
	void update();
private:
	int missilesLeft;
	int totalMissiles;
	sf::Vector2f sloap;
	std::vector<Missile*> activeMissiles;
};
