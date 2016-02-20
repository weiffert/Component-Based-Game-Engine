#include "stdafx.h"
#include "StatePause.h"
#include "SystemManager.h"
#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"



StatePause::StatePause(SystemManager *s, AssetManager *a)
{
	id = "Pause";
	number = 5;
	systemManager = s;
	assetManager = a;
}


StatePause::~StatePause()
{
}


void StatePause::update(double totalTime, sf::RenderWindow window)
{
	//Check for arrow key and space bar events
	sf::Event event;
	while (window.pollEvent(event))
	{
		bool moveUp = false, moveDown = false, moveRight = false, moveLeft = false, spaceBarReleased = false;

		//Checks if up arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
		{
			moveUp = true;
		}
		//Checks if down arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
		{
			moveDown = true;
		}
		//Checks if right arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
		{
			moveRight = true;
		}
		//Checks if left arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
		{
			moveLeft = true;
		}
		//Checks if space bar released
		if ((event.type = sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space))
		{
			spaceBarReleased = true;
		}
		//Checks if escape key pressed
		if ((event.type = sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape))
		{
			BaseState::changeState(this, "Menu");
		}
		//Run through the game controllers.
		//Example: Checking for collisions
		systemManager->getController("PlayerInput")->control(moveUp, moveDown, moveRight, moveLeft, spaceBarReleased, &material);
	}
}


void StatePause::render(double lag, sf::RenderWindow window)
{
	window.clear;
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->hasController("draw"))
		{
			BaseController *controller = material.at(i)->getController("draw");
			controller->control(material.at(i));
		}
	}
	window.display();
}
