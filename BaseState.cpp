#include "stdafx.h"

#include <string>
#include <vector>

#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "BaseState.h"
#include "Entity.h"
#include "SystemManager.h"
#include "AssetManager.h"


BaseState::BaseState()
{
}

BaseState::BaseState(SystemManager *s, AssetManager *a)
{
	id = "BaseState";
	number = -1;
	systemManager = s;
	assetManager = a;
}


BaseState::~BaseState()
{
	
}


int BaseState::getNumber()
{
	return number;
}


std::string BaseState::getId()
{
	return id;
}


void BaseState::setId(std::string a)
{
	id = a;
}


void BaseState::setNumber(int a)
{
	number = a;
}


void BaseState::setMaterial(std::vector<Entity*> a)
{
	material = a;
}


void BaseState::changeState(BaseState *a)
{
	int tempInt = a->getNumber();
	a = systemManager->getState(tempInt + 1);
}


void BaseState::changeState(BaseState *a, std::string s)
{
	a = systemManager->getState(s);
}


void BaseState::changeState(BaseState *a, int i)
{
	a = systemManager->getState(i);
}


void BaseState::render(double lag, sf::RenderWindow *window)
{
	window.clear;
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->hasController("Render"))
		{
			BaseController *controller = material.at(i)->getController("Render");
			controller->control(window, &material.at(i));
		}
	}
	window.display();
}
