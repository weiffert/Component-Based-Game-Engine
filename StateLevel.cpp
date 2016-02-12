#include "StateLevel.h"


StateLevel::StateLevel()
{
	id = "Level";
	number = 3;
	//Go through the entity list in the SystemManager and add them to the local list if the state property == "Level"
}


StateLevel::~StateLevel()
{
}


int StateLevel::update()
{
	//Check for arrow key and space bar events
	//Move the cursor respectively.
		//The cursor controller prevents the cursor from leaving a specific area.
	//Fire a missile if the space bar key is pressed.
		//The fire controller will handle firing if there is no missiles.
	
	//Run through the game controllers.
		//Example: Checking for collisions
		
	//If the wave is finished
		//Change to the next level.
		//I don't know if to do this using properties or making a whole new state.
}


void StateLevel::render()
{
	//Render the entities using the render controller.
	//Look something like render.control(*Entity, lag);
}
