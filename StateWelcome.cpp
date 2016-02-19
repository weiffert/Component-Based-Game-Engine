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

	//If total time is less than double waitTime,
		//return 0;
	//Else
		//return 1;
}


void StateWelcome::render(double lag, sf::RenderWindow)
{
}
