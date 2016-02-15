#include "StateLevel.h"
#include "SystemManager.h"

StateLevel::StateLevel(SystemManager *s)
{
	id = "Level";
	number = 3;
	systemManager = s;
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
		
	//If the wave is finished and the level continures (check the city number: an entity with the id of "city" and a property of live.)
		//Change to the next level. Color, velocity, and number of missiles has to change.
		//Pass through the enities. If one has one of these properties, change it.
	
	//else...
		//return -1;
}


void StateLevel::render(double lag)
{
	//Render the entities using the render controller.
	//Look something like render.control(*Entity, lag);
}
