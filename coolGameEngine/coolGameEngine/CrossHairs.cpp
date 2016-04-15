#include <string>

#include "Crosshairs.h"
#include "SystemManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

Crosshairs::Crosshairs()
{
  //Automatically set crosshairs to file "Crosshairs.png"
  if(file.loadFromFile("Crosshairs.png")
  {
    crosshair.setTexture(file);
    systemManager->getMaterial("Crosshairs")->deleteData();
    systemManager->getMaterial("Crosshairs")->addData(crosshair);
  }
}


Crosshairs::~Crosshairs()
{
}


void Crosshairs::loadTexture(std::string fileName, SystemManager * systemManager)
{
  crosshair.setTexture(fileName);
  file = fileName;
  systemManager->getMaterial("Crosshairs")->deleteData();
  systemManager->getMaterial("Crosshairs")->addData(crosshair);
}


void Crosshairs::control(sf::RenderWindow * renderWindow, SystemManager * systemManager)
{
  //Delete mouse position
  renderWindow.setMouseCursorVisible(false);
  
  //Update Crosshairs position
  crosshair.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
  
  //Update Crosshairs entity
  systemManager->getMaterial("Crosshairs")->deleteData();
  systemManager->getMaterial("Crosshairs")->addData(crosshair);
}
