#include "stdafx.h"

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include <stdlib.h>

#include "StateWelcome.h"
#include "StatePause.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Property.h"
#include "Entity.h"
//include controllers.

StateWelcome::StateWelcome(SystemManager *s, AssetManager *a)
{
	id = "Welcome";
	number = 1;
	systemManager = s;
	assetManager = a;
}


StateWelcome::~StateWelcome()
{
}

int StateWelcome::update(double totalTime, sf::RenderWindow *window)
{
	if (totalTime > 5)
		return 1;
	else
	{
		sleep(0.1);
		return 0;
	}
}