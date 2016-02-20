#include "stdafx.h"
#include "StateMenu.h"
#include "SystemManager.h"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

StateMenu::StateMenu(SystemManager *s, AssetManager *a)
{
	id = "Menu";
	number = 2;
	systemManager = s;
	assetManager = a;
}


StateMenu::~StateMenu()
{
}


void StateMenu::update(double totalTime, sf::RenderWindow window)
{
	//Check for arrow key and space bar events.
		//Arrow keys for navigation, space bar for selecting.
	//If arrow key event, change properties of the entities.
		//One looses the selector property and one gains it. Only one will have the selector property at a time.
	//If space bar event is the level,
		//return 1;
	//If the space bar event is quit, quit.
		//return -1;
	//else
		//return 0;
}


void StateMenu::render(double lag, sf::RenderWindow window)
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
