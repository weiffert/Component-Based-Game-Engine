#include "stdafx.h"

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "StateMenu.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Property.h"
#include "Entity.h"


StateMenu::StateMenu()
{
	//Sets defaults.
	id = "Menu";
	number = 2;
	systemManager = nullptr;
	assetManager = nullptr;
}

StateMenu::StateMenu(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "Menu";
	number = 2;
	systemManager = s;
	assetManager = a;
}


StateMenu::~StateMenu()
{
}


//Polls for events and calls the required controllers accordingly.
//Takes in the total time elapsed and the window.
std::string StateMenu::update(double totalTime, sf::RenderWindow* window)
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