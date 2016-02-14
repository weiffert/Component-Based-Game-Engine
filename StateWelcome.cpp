#include "StateWelcome.h"


StateWelcome::StateWelcome()
{
	id = "Welcome";
	number = 1;
}


StateWelcome::~StateWelcome()
{
}

int StateWelcome::update()
{
	//Any thoughts on how to do this without passing in values?
	//A simple solution is making provisions in the game loop, but that is messy.
	//Wait time step amount.
	//If total time is less than double waitTime,
		//return 1;
	//Else
		//return -1;
}


void StateWelcome::render(double lag)
{
	//Render the entities using the render controller.
	//Look something like render.control(*Entity, lag);
}
