#include "BaseState.h"
#include <string>


BaseState::BaseState()
{
	id = "NULL";
	number = -1;
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

