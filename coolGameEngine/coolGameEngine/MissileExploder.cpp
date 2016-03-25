#include "MissileExploder.h"
#include "Pro"
MissileExploder::MissileExploder()
{
}


MissileExploder::~MissileExploder()
{
}


void MissileExploder::control(sf::Window &window, Entity * missile)
{
  Property phase* = missile->getComponent("ExplosionPhase");
  Property radius* = missile->getComponent("ExplosionRadius");
  double rate;
  rate = 1;
  //If it doesn't already have an explosion, create one (property "ExplosionPhase" is 0)
  if (missile->getComponent("ExplosionPhase").at(0) == 0)
  {
    phase->deleteData();
    phase->addDataInt(1);
    tempRadius = missile->getComponent("ExplosionRadius")->getDataDouble().at(0);
    tempRadius += rate * missile->getComponent("ExplosionPhase")->getDataDouble().at(0);
    missile->getComponent("ExplosionRadius")->deleteData();
    missile->getComponent("ExplosionRadius")->addDataDouble(tempRadius);
  }
  
  //Check radius
  if ()
  
  //If it already has an explosion, change the size 
  
  
}
