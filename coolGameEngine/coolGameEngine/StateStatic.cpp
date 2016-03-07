#include "stdafx.h"

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include <stdlib.h>
#include <Windows.h>

#include "StateStatic.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Property.h"
#include "Entity.h"



StateStatic::StateStatic(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "Static";
	number = 1;
	systemManager = s;
	assetManager = a;
}


StateStatic::~StateStatic()
{
}


//Runs until a certain amount of time has elapsed.
//Takes in a double which contains the amount of time elapsed. Takes in the window for consistency.
void StateStatic::update(double totalTime, sf::RenderWindow *window)
{
	//If the game has been running for more than five seconds, change states.
	if (totalTime > 5)
		BaseState::changeState(this, "Menu");

	else
	{
		Sleep(0.1);
	}
}
