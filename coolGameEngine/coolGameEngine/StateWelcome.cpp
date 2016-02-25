#include "stdafx.h"

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include <stdlib.h>
#include <Windows.h>

#include "StateWelcome.h"
#include "StatePause.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Property.h"
#include "Entity.h"



StateWelcome::StateWelcome(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "Welcome";
	number = 1;
	systemManager = s;
	assetManager = a;
}


StateWelcome::~StateWelcome()
{
}


//Runs until a certain amount of time has elapsed.
//Takes in a double which contains the amount of time elapsed. Takes in the window for consistency.
void StateWelcome::update(double totalTime, sf::RenderWindow *window)
{
	//If the game has been running for more than five seconds, change states.
	if (totalTime > 5)
		BaseState::changeState(this, "Menu");

	else
	{
		Sleep(0.1);
	}
}