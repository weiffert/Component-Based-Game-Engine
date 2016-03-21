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
	double setSlope(Entity*, int, int);
	void update();
private:
	int missilesLeft;
	int totalMissiles;
};
