#include "StatePause.h"
#include "SystemManager.h"
//SFML includes


StatePause::StatePause(SystemManager *s)
{
	id = "Pause";
	number = 5;
	systemManager = s;
}


StatePause::~StatePause()
{
}


int StatePause::update(double totalTime)
{
	//Check for arrow key and space bar events.
		//Arrow keys for navigation, space bar for selecting.
	//If arrow key event, change properties of the entities.
		//One looses the selector property and one gains it. Only one will have the selector property at a time.
	//If space bar event is the level,
		//return 1;
	//If the space bar event is menu,
		//return 2;
	//else
		//return 0;
}


void StatePause::render(double lag, sf::RenderWindow)
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
