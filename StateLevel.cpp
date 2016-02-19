#include "StateLevel.h"
#include "SystemManager.h"
//SFML includes

StateLevel::StateLevel(SystemManager *s)
{
	id = "Level";
	number = 3;
	systemManager = s;
}


StateLevel::~StateLevel()
{
}


int StateLevel::update(double totalTime)
{
	//Check for arrow key and space bar events
	//Move the cursor respectively.
		//The cursor controller prevents the cursor from leaving a specific area.
	//Fire a missile if the space bar key is pressed.
		//The fire controller will handle firing if there is no missiles.
	
	//Run through the game controllers.
		//Example: Checking for collisions
		
	//If the game is not done...
		//If the wave is finished and the level continures (check the city number: an entity with the id of "city" and a property of live.)
			//Change to the next level. Color, velocity, and number of missiles has to change.
			//Pass through the enities. If one has one of these properties, change it.
		//return 0;
	
	//else...
		//return 1;
}


void StateLevel::render(double lag, sf::RenderWindow)
{
	w.clear;
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->hasComponent("draw"))
		{
			//Needs to be a drawable.
			w.draw(material.at(i));
		}
	}
	w.display();
}
