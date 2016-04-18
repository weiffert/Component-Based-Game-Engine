#include <string>
#include <iostream>
#include "Crosshairs.h"
#include "SystemManager.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Entity.h"
#include "Property.h"

Crosshairs::Crosshairs()
{
  
}


Crosshairs::~Crosshairs()
{

}


void Crosshairs::control(sf::RenderWindow * window, SystemManager * systemManager)
{
  //Delete mouse position
  window->setMouseCursorVisible(false);
  
  //Update Crosshairs position
  crosshair = systemManager->getMaterial("Crosshairs")->getComponent("Sprite")->getDataSprite().at(0);
  sf::Vector2f position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
  double tempX = position.x;
  double tempY = position.y;
  tempX =  tempX - crosshair->getGlobalBounds().width / 2;
  tempY = tempY - crosshair->getGlobalBounds().height / 2 ;
  position = sf::Vector2f(tempX, tempY);
  crosshair->setPosition(position);
}

void Crosshairs::fitSize(SystemManager * systemManager, int size)
{
	crosshair = systemManager->getMaterial("Crosshairs")->getComponent("Sprite")->getDataSprite().at(0);
	float scale = size / crosshair->getLocalBounds().height;
	crosshair->setScale(sf::Vector2f(scale, scale)); //crosshair is a pointer this is saved
}