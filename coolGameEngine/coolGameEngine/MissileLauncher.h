#pragma once
class MissileLauncher
{
public:
	MissileLauncher();
	~MissileLauncher();
	int fire(Entity *, Entity *, sf::Window *, SystemManager *);	//Returns 0 if it fails to launch, 1 if it successfully launches
	void setMissilesLeft(int);
	void setTotalMissiles(int);
	int getMissilesLeft();
	int getTotalMissiles();
	double setSlope(int, int);
	void update();
private:
	int missilesLeft;
	int totalMissiles;
};
