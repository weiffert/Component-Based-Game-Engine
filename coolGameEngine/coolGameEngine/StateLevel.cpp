#include "stdafx.h"

#include <string>
#include <vector>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "StateLevel.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "BaseState.h"
#include "Entity.h"
#include "Property.h"

//include controllers
#include "MissileLauncher.h"
#include "MissileLauncherAi.h"
#include "Crosshairs.h"
#include "MissileChecker.h"
#include "ScoreKeeper.h"
#include "LevelChange.h"
#include "Plane.h"

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
std::string StateLevel::update(double totalTime, sf::RenderWindow* window)
{
	MissileLauncher missileLauncher;
	MissileLauncherAi missileLauncherAi(assetManager, systemManager);
	ScoreKeeper  scoreKeeper;
	Crosshairs crosshairs; 
	MissileChecker missileChecker;
	LevelChange levelChange;
	Plane planeController(systemManager, assetManager);

	Entity * player = systemManager->getMaterial("Player");


	bool found;

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
			found = false;
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
			found = false;
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
			found = false;
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
	}

	std::vector<Entity *> missiles = systemManager->getMaterial("MissileLauncherAi")->getComponent("MissilesHeld")->getDataEntity();
	bool determineCitites = true;

	for (int i = 0; i < missiles.size(); i++)
	{
		if (missiles.at(i)->getComponent("Fired")->getDataBool().at(0) == true)
			determineCitites = false;
	}


	Entity * launcherAi = systemManager->getMaterial("MissileLauncherAi");

	if (launcherAi->getComponent("SetTargets")->getDataBool().at(0) == false)
	{
		launcherAi->getComponent("SetTargets")->deleteData();
		launcherAi->getComponent("SetTargets")->addData(true);

		//Determine cities surviving
		bool cities[6];
		cities[0] = systemManager->getMaterial("City1")->getComponent("Life")->getDataBool().at(0);
		cities[1] = systemManager->getMaterial("City2")->getComponent("Life")->getDataBool().at(0);
		cities[2] = systemManager->getMaterial("City3")->getComponent("Life")->getDataBool().at(0);
		cities[3] = systemManager->getMaterial("City4")->getComponent("Life")->getDataBool().at(0);
		cities[4] = systemManager->getMaterial("City5")->getComponent("Life")->getDataBool().at(0);
		cities[5] = systemManager->getMaterial("City6")->getComponent("Life")->getDataBool().at(0);
		missileLauncherAi.setTargets(cities);
	}

	//Create timer for delaying firing new enemy missiles

	//fire enemy missiles
	found = false;
	int decrement = 29;
	Entity *missile = nullptr;

	if (rand() % launcherAi->getComponent("FireRate")->getDataInt().at(0) == 0)  //Occurs at relatively random times.
	{
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
	}
	if (found)
	{
		missileLauncherAi.launchMissiles(missile, window);
	}

	missileChecker.control(window, systemManager);
	planeController.update(window); //Planes should be self-reliant 
	missileLauncher.update(systemManager, window, systemManager->getMaterial("Base1"), systemManager->getMaterial("Base2"), systemManager->getMaterial("Base3"));
	missileLauncherAi.update(window, launcherAi);
	crosshairs.control(window, systemManager);
	std::string stateChange = levelChange.control(systemManager, assetManager, window);

	return stateChange;
}