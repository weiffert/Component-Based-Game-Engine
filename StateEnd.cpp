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


int StateEnd::update()
{
	//Any thoughts on how to do this without passing in values?
	//A simple solution is making provisions in the game loop, but that is messy.
	//Wait time step amount.
	//If total time is less than double waitTime,
		//return 1;
	//Else
		//return -1;
}


void StateEnd::render(double lag, sf::RenderWindow)
{
}
