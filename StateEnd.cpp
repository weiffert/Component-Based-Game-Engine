#include "StateEnd.h"


StateEnd::StateEnd()
{
	id = "End";
	number = 4;
}


StateEnd::~StateEnd()
{
}


int StateEnd::update()
{
	//basically the same as StateWelcome.
}


void StateEnd::render(double lag)
{
	//Render the entities using the render controller.
	//Look something like render.control(*Entity, lag);
}
