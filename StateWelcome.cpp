#include "stdafx.h"

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "StatePause.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Property.h"
#include "Entity.h"
//include controllers.

StateWelcome::StateWelcome(SystemManager *s)
{
	id = "Welcome";
	number = 1;
	systemManager = s;
}


StateWelcome::~StateWelcome()
{
}

int StateWelcome::welcomeUpdate(double totalTime)
{
	if (totalTime > 5)
		return 1;
	else
	{
		sleep(0.1);
		return 0;
	}
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