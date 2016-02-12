#include "StateMenu.h"


StateMenu::StateMenu()
{
	id = "Menu";
	number = 2;
}


StateMenu::~StateMenu()
{
}


int StateMenu::update()
{
	//Check for arrow key and space bar events.
		//Arrow keys for navigation, space bar for selecting.
	//If arrow key event, change properties of the entities.
		//One looses the selector property and one gains it. Only one will have the selector property at a time.
	//If space bar event is the level,
		//return 2;
	//If the space bar event is quit, quit.
		//return -1;		-1 is kind of the standard for quitting it seems.
	//else
		//return 1;
}


void StateMenu::render(double lag)
{
	//Render the entities using the render controller.
	//Look something like render.control(*Entity, lag);
}
