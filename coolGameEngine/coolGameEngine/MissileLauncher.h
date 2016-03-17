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
private:
	int missilesLeft;
	int totalMissiles;
};
