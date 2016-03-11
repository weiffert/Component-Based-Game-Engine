#include "stdafx.h"

#include <string>
#include <vector>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
//#include "PlayerInput.h"

#include "StateLevel.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "BaseState.h"
#include "Entity.h"
#include "Property.h"
//include controllers


StateLevel::StateLevel()
{
	//Sets defaults.
	id = "Level";
	number = 3;
	systemManager = nullptr;
	assetManager = nullptr;
}


StateLevel::StateLevel(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "Level";
	number = 3;
	systemManager = s;
	assetManager = a;
}


StateLevel::~StateLevel()
{
}


//Polls for events and calls the required controllers accordingly.
//Takes in the total time elapsed and the window.
void StateLevel::update(double totalTime, sf::RenderWindow* window)
{
	//Check for arrow key and space bar events
	sf::Event event;
	while (window->pollEvent(event))
	{
		bool moveUp = false, moveDown = false, moveRight = false, moveLeft = false, spaceBarReleased = false;

		//Checks if up arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
		{
			moveUp = true;
		}
		//Checks if down arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
		{
			moveDown = true;
		}
		//Checks if right arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
		{
			moveRight = true;
		}
		//Checks if left arrow key pressed
		if ((event.type = sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
		{
			moveLeft = true;
		}
		//Checks if space bar released
		if ((event.type = sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space))
		{
			spaceBarReleased = true;
		}
		//Checks if escape key pressed
		if ((event.type = sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape))
		{
			BaseState::changeState(this, "Pause");
		}
		//Run through the game controllers.
		//Example: Checking for collisions
		//systemManager->getController("PlayerInput")->control(moveUp, moveDown, moveRight, moveLeft, spaceBarReleased, &material);
		//Controls the Ai of the game
		//systemManager->getController("Ai")->control(&material);
		//If the game is not done...
		//If the wave is finished and the level continures (check the city number: an entity with the id of "city" and a property of live.)
		//Change to the next level. Color, velocity, and number of missiles has to change.
		//Pass through the enities. If one has one of these properties, change it.
		//return 't';
		//else...
		//return 'f';
		//systemManager->getController("GameEnd")->control(&material);
	}
}