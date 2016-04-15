#include <string>

#include "Crosshairs.h"
#include "SystemManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Entity.h"
#include "Property.h"

Crosshairs::Crosshairs()
{
  
}

Crosshairs::Crosshairs(SystemManager * systemManager)
{
	//Automatically set crosshairs to file "Crosshairs.png"
	if (file.loadFromFile("Crosshairs.png"))
	{
		crosshair->setTexture(file);
		systemManager->getMaterial("Crosshairs")->getComponent("Sprite")->deleteData();
		systemManager->getMaterial("Crosshairs")->getComponent("Sprite")->addData(crosshair);
	}
}


Crosshairs::~Crosshairs()
{

}


void Crosshairs::loadTexture(std::string fileName, SystemManager * systemManager)
{
file.loadFromFile(fileName);
  crosshair->setTexture(file);
 
  systemManager->getMaterial("Crosshairs")->getComponent("Sprite")->deleteData();
  systemManager->getMaterial("Crosshairs")->getComponent("Sprite")->addData(crosshair);
}


void Crosshairs::control(sf::RenderWindow * renderWindow, SystemManager * systemManager)
{
  //Delete mouse position
  renderWindow->setMouseCursorVisible(false);
  
  //Update Crosshairs position
  crosshair->setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*renderWindow)));
  
  //Update Crosshairs entity
  systemManager->getMaterial("Crosshairs")->getComponent("Sprite")->deleteData();
  systemManager->getMaterial("Crosshairs")->getComponent("Sprite")->addData(crosshair);
}
