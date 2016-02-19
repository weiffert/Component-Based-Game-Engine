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


void StateEnd::render(double lag, sf::RenderWindow)
{
}
