#pragma once


class MissileGuidance
{
  private:
    
    int pathX, pathY;
    
    sf::Vector2f sloap;
  
  
  public:
  
    MissileGuidance();
    
    MissileGuidance(int);
    
    void findBase();
    
    ~MissileGuidance();
  
}
