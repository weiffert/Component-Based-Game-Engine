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


StateStatic::StateStatic()
{
	//Sets defaults.
	id = "Static";
	number = 1;
	systemManager = nullptr;
	assetManager = nullptr;
}


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


//Polls for events and calls the required controllers accordingly.
//Takes in the total time elapsed and the window.
std::string StateStatic::update(double totalTime, sf::RenderWindow* window)
{
	//Initialize controllers.


	sf::Event event;
	while (window->pollEvent(event))
	{
		//Event handling.
	}

	//Perform state updates.


	//Return a string for determining which state to remain in.
	return "string";
}

