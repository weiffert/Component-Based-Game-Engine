#pragma once
class MissileLauncher
{
public:
	MissileLauncher();
	~MissileLauncher();
	int getMissiles();
	void fire();
	void setMissilesLeft();
	void setTotalMissiles();
private:
	int missilesLeft;
	int totalMissiles;
};
