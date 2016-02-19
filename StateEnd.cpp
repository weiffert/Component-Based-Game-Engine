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
	if (totalTime > 5)
		return -1;
	else
	{
		sleep(0.1);
		return 1;
	}

	//If total time is less than double waitTime,
	//return 1;
	//Else
	//return -1;
}


void StateEnd::render(double lag, sf::RenderWindow)
{
}
