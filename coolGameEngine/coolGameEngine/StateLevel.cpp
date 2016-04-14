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
#include "MissileLauncher.h"


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
	MissileLauncher missileLauncher;
	//MissileLauncherAi missileLauncherAi;

	//Check for arrow key and space bar events
	sf::Event event;
	while (window->pollEvent(event))
	{
		//Checks if escape key pressed
		if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape))
			//BaseState::changeState(this, "Pause");
			window->close();
		if (event.type == sf::Event::Closed)
			window->close();

		centerCoordinates.x = (window->getSize().x) / 2;
		centerCoordinates.y = (window->getSize().y) / 2;

		//sf::Mouse::setPosition(centerCoordinates, *window);

		bool moveUp = false, moveDown = false, moveRight = false, moveLeft = false, spaceBarReleased = false;

		//Checks if trackball moved up
		if (sf::Mouse::getPosition(*window).y > centerCoordinates.y)
			moveUp = true;
		//Checks if trackball moved down
		if (sf::Mouse::getPosition(*window).y < centerCoordinates.y)
			moveDown = true;
		//Checks if trackball moved right
		if (sf::Mouse::getPosition(*window).x > centerCoordinates.x)
			moveRight = true;
		//Checks if trackball moved left
		if (sf::Mouse::getPosition(*window).x < centerCoordinates.x)
			moveLeft = true;

		//Launch from base1;
		if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::A))
		{
			bool found = false;
			int decrement = 9;
			Entity *missile = nullptr;
			std::vector<Entity *> missiles = systemManager->getMaterial("Base1")->getComponent("MissilesHeld")->getDataEntity();
			while (!found && decrement >= 0)
			{
				if (missiles.at(decrement)->hasComponent("Fired"))
				{
					if (missiles.at(decrement)->getComponent("Fired")->getDataBool().at(0) == false)
					{
						found = true;
						missile = missiles.at(decrement);
					}
				}
				decrement--;
			}
			if (found)
			{
				//Play fired sound.
				if (missile->hasComponent("SoundSwoopUp"))
				{
					sf::Sound s;
					s.setBuffer(*(missile->getComponent("SoundSwoopUp")->getDataSoundBuffer().at(0)));
					s.play();
				}
				missileLauncher.fire(missile, systemManager->getMaterial("Base1"), window, systemManager, assetManager);
			}
			else
			{
				//Play no missiles sound.
				if (missiles.at(0)->hasComponent("SoundMissileFireFail"))
				{
					sf::Sound s;
					s.setBuffer(*(missiles.at(0)->getComponent("SoundMissileFireFail")->getDataSoundBuffer().at(0)));
					s.play();
				}
			}
		}
		//Launch from base2;
		if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::S))
		{
			bool found = false;
			int decrement = 9;
			Entity *missile = nullptr;
			std::vector<Entity *> missiles = systemManager->getMaterial("Base2")->getComponent("MissilesHeld")->getDataEntity();
			while (!found && decrement >= 0)
			{
				if (missiles.at(decrement)->hasComponent("Fired"))
				{
					if (missiles.at(decrement)->getComponent("Fired")->getDataBool().at(0) == false)
					{
						found = true;
						missile = missiles.at(decrement);
					}
				}
				decrement--;
			}
			if (found)
			{
				//Play fired sound.
				if (missile->hasComponent("SoundSwoopUp"))
				{
					sf::Sound s;
					s.setBuffer(*(missile->getComponent("SoundSwoopUp")->getDataSoundBuffer().at(0)));
					s.play();
				}
				missileLauncher.fire(missile, systemManager->getMaterial("Base2"), window, systemManager, assetManager);
			}
			else
			{
				//Play no missiles sound.
				if (missiles.at(0)->hasComponent("SoundMissileFireFail"))
				{
					sf::Sound s;
					s.setBuffer(*(missiles.at(0)->getComponent("SoundMissileFireFail")->getDataSoundBuffer().at(0)));
					s.play();
				}
			}
		}
		//Launch from base3;
		if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::D))
		{
			bool found = false;
			int decrement = 9;
			Entity *missile = nullptr;
			std::vector<Entity *> missiles = systemManager->getMaterial("Base3")->getComponent("MissilesHeld")->getDataEntity();
			while (!found && decrement >= 0)
			{
				if (missiles.at(decrement)->hasComponent("Fired"))
				{
					if (missiles.at(decrement)->getComponent("Fired")->getDataBool().at(0) == false)
					{
						found = true;
						missile = missiles.at(decrement);
					}
				}
				decrement--;
			}
			if (found)
			{
				//Play fired sound.
				if (missile->hasComponent("SoundSwoopUp"))
				{
					sf::Sound s;
					s.setBuffer(*(missile->getComponent("SoundSwoopUp")->getDataSoundBuffer().at(0)));
					s.play();
				}
				missileLauncher.fire(missile, systemManager->getMaterial("Base3"), window, systemManager, assetManager);
			}
			else
			{
				//Play no missiles sound.
				if (missiles.at(0)->hasComponent("SoundMissileFireFail"))
				{
					sf::Sound s;
					s.setBuffer(*(missiles.at(0)->getComponent("SoundMissileFireFail")->getDataSoundBuffer().at(0)));
					s.play();
				}
			}
		}

		//Run through the game controllers.
		//Example: Checking for collisions
		//systemManager->getController("PlayerInput")->control(moveUp, moveDown, moveRight, moveLeft, spaceBarReleased, &material);
		//If the game is not done...
		//If the wave is finished and the level continures (check the city number: an entity with the id of "city" and a property of live.)
		//Change to the next level. Color, velocity, and number of missiles has to change.
		//Pass through the enities. If one has one of these properties, change it.
		//return 't';
		//else...
		//return 'f';
	}

	missileLauncher.update(window, systemManager->getMaterial("Base1"), systemManager->getMaterial("Base2"), systemManager->getMaterial("Base3"));
	//missileLauncherAi.
}