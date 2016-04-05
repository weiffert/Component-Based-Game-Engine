#pragma once
class MissileLauncherAi
{
private:
  int missilesLeft, totalMissiles, targetOne, targetTwo, targetThree;

public:
  MissileLauncherAi();
  MissileLauncherAi(int, int);
  ~MissleLauncherAi();
  void setTargets();
  double setSlope(Entity*, int, int);
  void setTotalMissiles(int);
  void setMissilesLeft(int);
  int getMissilesLeft();
	int getTotalMissiles();
  int launchMissiles(Entity *, Entity *, sf::Window & ); //Returns 0 if it fails to launch, 1 if it successfully launches
  void update();
  

