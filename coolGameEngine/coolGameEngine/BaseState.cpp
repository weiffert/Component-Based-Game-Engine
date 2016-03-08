#include "stdafx.h"

#include <string>
#include <vector>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "BaseState.h"
#include "Entity.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Render.h"


BaseState::BaseState()
{
}


BaseState::BaseState(SystemManager *s, AssetManager *a)
{
	//Set defaults.
	id = "BaseState";
	number = -1;
	systemManager = s;
	assetManager = a;
}


BaseState::~BaseState()
{
	
}


//Returns the id number.
int BaseState::getNumber()
{
	return number;
}


//Returns the id string.
std::string BaseState::getId()
{
	return id;
}


//Sets the id.
//Takes in a string.
void BaseState::setId(std::string a)
{
	id = a;
}


//Set the id number.
//Takes in an int.
void BaseState::setNumber(int a)
{
	number = a;
}


//Sets the materials in the state.
//Takes in a vector of predefined entity pointers.
void BaseState::setMaterial(std::vector<Entity*> a)
{
	material = a;
}


//Render the state onto the window.
//Takes in the amount of time lag and the window.
void BaseState::render(double lag, sf::RenderWindow *window)
{
	window->clear;

	Render controller;
	///Pass through all of the materials.
	for (int i = 0; i < material.size(); i++)
	{
		/*
		if (material.at(i)->hasController("Render"))
		{
			BaseController *controller = material.at(i)->getController("Render");
			controller->control(window, &material.at(i));
		}
		*/
		//Render the current entity.
		controller.control(lag, window, material.at(i));
	}

	window->display();
}


//Change the state to the next in numerical order.
void BaseState::changeState(BaseState *a)
{
	int tempInt = a->getNumber();
	a = systemManager->getState(tempInt + 1);
}


//Change the state to the next by string id.
void BaseState::changeState(BaseState *a, std::string s)
{
	a = systemManager->getState(s);
}


//Change the state to the next by number id.
void BaseState::changeState(BaseState *a, int i)
{
	a = systemManager->getState(i);
}