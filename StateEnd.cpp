#include "StateEnd.h"
#include "SystemManager.h"
#include "BaseController.h"
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
		if (material.at(i)->hasController("draw"))
		{
			BaseController *controller = material.at(i)->getController("draw");
			controller->control(material.at(i));
		}
	}
	w.display();
}
