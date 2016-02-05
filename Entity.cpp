#include "Entity.h"
#include <string>
#include "vector"
#include "BaseComponent"
#include "BaseController"

string Entity::getId()
{
	return id;
}

string Entity::setId(string newId)
{
	id = newId;
}

void Entity::addComponent(*BaseComponent newComponent)
{
	components.push_back(newComponent);
}

void Entity::removeComponent()
{
	components.pop_back();
}

*BaseComponent Entity::getComponent()
{
	return components;
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

void Entity::addController(*BaseController newComponent)
{
	controllers.push_back(newComponent);
}

void Entity::removeController()
{
	controllers.pop_back();
}

*BaseController Entity::getController()
{
	return controller;
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