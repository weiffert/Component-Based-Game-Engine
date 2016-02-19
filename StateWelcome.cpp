#include "StateWelcome.h"
#include "SystemManager.h"
//SFML includes

StateWelcome::StateWelcome(SystemManager *s)
{
	id = "Welcome";
	number = 1;
	systemManager = s;
}


StateWelcome::~StateWelcome()
{
}

int StateWelcome::update(double totalTime)
{
	if (totalTime > 5)
		return 1;
	else
	{
		sleep(0.1);
		return 0;
	}
}


void StateWelcome::render(double lag, sf::RenderWindow)
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
