#include "stdafx.h"
#include "Entity.h"
#include <string>
#include "vector"
#include "BaseComponent.h"
#include "BaseController.h"


Entity::Entity()
{

}


Entity::~Entity()
{

}


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


//Removes all components with the same string id.
void Entity::removeComponent(std::string id)
{
	for (int i = 0; i < components.size())
	{
		if (components.at(i)->getId == id)
		{
			delete *components.at(i);
			components.erase(i, i);
		}
	}
}



bool Entity::hasComponent(std::string)
{
	for (int i = 0; i < components.size())
	{
		if (components.at(i).getId == id)
			return true;
	}

	return false;
}


void Entity::addController(BaseController* newComponent)
{
	controllers.push_back(newComponent);
}


void Entity::removeController(std::string)
{
	for (int i = 0; i < controllers.size())
	{
		if (controllers.at(i)->getId == id)
		{
			delete *controllers.at(i);
			controllers.erase(i, i);
		}
	}
}


bool Entity::hasController(std::string)
{
	for (int i = 0; i < controllers.size())
	{
		if (controllers.at(i).getId == id)
			return true;
	}
	
	return false;
}
