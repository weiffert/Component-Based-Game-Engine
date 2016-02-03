#include "stdafx.h"
#include "BaseComponent.h"


BaseComponent::BaseComponent()
{
	id = "BaseComponent"; //Autoset the id to BaseComponent
}


BaseComponent::~BaseComponent()
{
}


//Returns id
string BaseComponent::getId()
{
	return id;
}


//Sets id
void BaseComponent::setId(string a)
{
	id = a;
	return;
}