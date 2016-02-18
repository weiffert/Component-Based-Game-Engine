#include "BaseState.h"
#include "SystemManager.h"
#include <string>


BaseState::BaseState(SystemManager *s)
{
	id = "BaseState";
	number = -1;
	systemManager = s;
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