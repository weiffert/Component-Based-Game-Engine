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
