#pragma once
class MissileLauncher
{
public:
	MissileLauncher();
	~MissileLauncher();
	int getMissiles();
	void fire();
	void setMissilesLeft(int);
	void setTotalMissiles(int);
	int getMissilesLeft();
	int getTotalMissiles();
private:
	int missilesLeft;
	int totalMissiles;
};
