#include "BaseState.h"
#include "SystemManager.h"
#include <string>


BaseState::BaseState(SystemManager *s)
{
	id = "NULL";
	number = -1;
	systemManager = s;
}


BaseState::~BaseState()
{
	
}


void BaseState::update()
{
}


void BaseState::render()
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

