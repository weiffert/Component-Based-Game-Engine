#include "stdafx.h"
#include "StateEnd.h"
#include "AssetManager.h"
#include "SystemManager.h"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
//SFML includes

StateEnd::StateEnd(SystemManager *s, AssetManager *a)
{
	id = "End";
	number = 4;
	systemManager = s;
	assetManager = a;
}


StateEnd::~StateEnd()
{
}


void StateEnd::update(double totalTime, sf::RenderWindow window)
{
	//this could reinitialize the levels.
}


void StateEnd::render(double lag, sf::RenderWindow window)
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
