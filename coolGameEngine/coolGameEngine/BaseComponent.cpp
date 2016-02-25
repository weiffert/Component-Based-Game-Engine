#include "stdafx.h"

#include <string>

#include "BaseComponent.h"


BaseComponent::BaseComponent()
{ 
	//Autoset the id to BaseComponent
	id = "BaseComponent";
}


BaseComponent::~BaseComponent()
{
}


//Returns id
std::string BaseComponent::getId()
{
	return id;
}


//Sets id
//Takes in a string.
void BaseComponent::setId(std::string a)
{
	id = a;
}
