#include "stdafx.h"
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include <string>


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