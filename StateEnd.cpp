#include "stdafx.h"
#include "StateEnd.h"
#include "SystemManager.h"
//SFML includes

StateEnd::StateEnd(SystemManager *s)
{
	id = "End";
	number = 4;
	systemManager = s;
}


StateEnd::~StateEnd()
{
}


int StateEnd::update(double totalTime)
{
	//this could reinitialize the levels.
}


void StateEnd::render(double lag, sf::RenderWindow w)
{
	w.clear;
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->hasComponent("draw"))
		{
			//Needs to be a drawable.
			w.draw(material.at(i));
		}
	}
	w.display();
}
