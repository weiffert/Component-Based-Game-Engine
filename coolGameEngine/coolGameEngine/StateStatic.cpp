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


//Runs until a certain amount of time has elapsed.
//Takes in a double which contains the amount of time elapsed. Takes in the window for consistency.
std::string StateStatic::update(double totalTime, sf::RenderWindow *window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
				window->close();
			else
			{
				if (id.find("GameOver") == std::string::npos)
					return "next";
				else
					window->close();
			}
		}
	}
	if (id.find("GameOver") != std::string::npos)
	{
		Property *t = systemManager->getMaterial("GameOver")->getComponent("Text");
		sf::Text *text = new sf::Text;
		text->setString(std::to_string(systemManager->getMaterial("Player")->getComponent("Points")->getDataInt().at(0)));
		text->setPosition(0, 50);
		
		t->addData(text);
 
		//Play sound
		sf::Sound * sound = new sf::Sound;
		sf::SoundBuffer buffer = *systemManager->getComponent("SoundGameOver")->getDataSoundBuffer().at(0);
		sound->setBuffer(buffer);
		sound->play();
		assetManager->add(sound);
		assetManager->add(&buffer);
		
	}
	
	return "constant";
}
