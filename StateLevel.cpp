#include "StateLevel.h"
#include "SystemManager.h"
#include "BaseState.h"
#include "SFML\Audio.hpp"
#include "SFML\Grahpics.hpp"
#include "PlayerInput.h"
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


void StateLevel::update(double totalTime, sf::RenderWindow window)
{
	//Check for arrow key and space bar events
	sf::Event event
	while (window.pollEvent(event))
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
			moveLeft = true
		}
		//Checks if space bar released
		if ((event.type = sf::Event::KeyRelease) && (event.key.code == sf::Keyboard::Spacebar))
		{
			spaceBarReleased = true;
		}
		//Checks if escape key pressed
		if ((event.type = sf::Event::KeyRelease) && (event.key.code == sf::Keyboard::Escape))
		{
			BaseState::changeState(this,"Pause");
		}
		//Run through the game controllers.
		//Example: Checking for collisions
		systemManager->getController("PlayerInput")->control(moveUp, moveDown, moveRight, moveLeft, spaceBarReleased, &material);
		//Controls the Ai of the game
		systemManager->getController("Ai")->control(&material);
		//If the game is not done...
		//If the wave is finished and the level continures (check the city number: an entity with the id of "city" and a property of live.)
		//Change to the next level. Color, velocity, and number of missiles has to change.
		//Pass through the enities. If one has one of these properties, change it.
		//return 't';
		//else...
		//return 'f';
		systemManager->getController("GameEnd")->control(&material);
	}
}

//Clears and Draws new frames to the game window
void StateLevel::render(double lag, sf::RenderWindow window)
{
	window.clear;
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->hasController("draw"))
		{
			BaseController *controller = material.at(i)->getController("draw");
			controller->control(material.at(i));
		}
	}
	window.display();
}
