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
	id = "BaseState";
	number = -1;
	systemManager = nullptr;
	assetManager = nullptr;
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
	window->clear();

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


//Convert a string to an int.
int BaseState::conversionInt(std::string s)
{
	int temp = 0;

	//Repeat until the number has been extracted.
	for (int i = 0; i < s.length(); i++)
	{
		//Conversion from string to base 10.
		temp *= 10;
		temp += static_cast<int>(s.at(i) - 48);
	}

	return temp;
}


//Convert a string to a float.
float BaseState::conversionFloat(std::string s)
{
	float temp = 0;
	int place = 0;

	bool decimal = false;
	//Repeat until the number has been extracted.
	for (int i = 0; i < s.length(); i++)
	{
		//Conversion from string to base 10.
		if (s.at(i) == '.')
		{
			decimal = true;
		}

		if (!decimal)
		{
			temp *= 10;
			temp += static_cast<int>(s.at(i) - 48);
		}
		else
		{
			place += 10;
			int small = static_cast<int>(s.at(i) - 48);
			small /= place;
			temp += small;
		}
	}

	return temp;
}