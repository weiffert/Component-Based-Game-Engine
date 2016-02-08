#include "stdafx.h"
#include "Entity.h"
#include <string>
#include "vector"
#include "BaseComponent.h"
#include "BaseController.h"


std::string Entity::getId()
{
	return id;
}


void Entity::setId(std::string newId)
{
	id = newId;
}


void Entity::addComponent(BaseComponent* newComponent)
{
	components.push_back(newComponent);
}


void Entity::removeComponent()
{
	components.pop_back();
}


//The purpose of this function is not clear from the documentation
//so a "stub" has been made
BaseComponent* Entity::getComponent()
{
	BaseComponent* stub;
	return stub;
}


bool Entity::hasComponent()
{
	if (components.empty() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Entity::addController(BaseController* newComponent)
{
	controllers.push_back(newComponent);
}


void Entity::removeController()
{
	controllers.pop_back();
}


//The purpose of this function is not clear from the documentation
//so a "stub" has been made
BaseController* Entity::getController()
{
	BaseController* stub;
	return stub;
}


bool Entity::hasController()
{
	if (components.empty() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}
