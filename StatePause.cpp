#include "StatePause.h"


StatePause::StatePause()
{
	id = "Pause";
	number = 5;
}


StatePause::~StatePause()
{
}


int StatePause::update()
{
	//same event handling as StateMenu.
	//If return to game,
		//return 2;
	//If exit,
		//return -1;
	//else
		//return 1;
}


void StatePause::render(double lag)
{
	//Render the entities using the render controller.
	//Look something like render.control(*Entity, lag);
}
