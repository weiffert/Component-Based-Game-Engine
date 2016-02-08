#include "BaseComponent.h"


BaseComponent::BaseComponent()
{
	id = "BaseComponent"; //Autoset the id to BaseComponent
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
void BaseComponent::setId(std::string a)
{
	id = a;
	return;
}
