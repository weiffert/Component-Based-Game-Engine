#include "StateWelcome.h"


StateWelcome::StateWelcome()
{
	id = "Welcome";
	number = 0;
}


StateWelcome::~StateWelcome()
{
}

void StateWelcome::update()
{
	//Wait time step amount.
}


void StateWelcome::render(double lag)
{
	//Render the entities using the render controller.
	//Look something like render.control(*Entity, lag);
}
