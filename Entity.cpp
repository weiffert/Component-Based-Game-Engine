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
	component.push_back(newComponent);
}


void Entity::addController(BaseController* newComponent)
{
	controller.push_back(newComponent);
}


void Entity::remove(BaseComponent *a)
{
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i) == a)
		{
			delete component.at(i);
			component.erase(i);
		}
	}
}


void Entity::remove(BaseController *a)
{
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i) == a)
		{
			delete controller.at(i);
			controller.erase(i);
		}
	}
}


void Entity::deleteComponent(std::string id)
{
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == id)
		{
			delete component.at(i);
			component.erase(i);
		}
	}
}


void Entity::deleteController(std::string id)
{
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i)->getId() == id)
		{
			delete controller.at(i);
			controller.erase(i);
		}
	}
}


bool Entity::hasComponent(std::string id)
{
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == id)
			return true;
	}

	return false;
}



bool Entity::hasController(std::string id)
{
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i)->getId() == id)
			return true;
	}
	
	return false;
}


BaseComponent* Entity::getComponent(std::string id)
{
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == id)
			return component.at(i);
	}

	return nullptr;
}


BaseController* Entity::getController(std::string id)
{
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i)->getId() == id)
			return controller.at(i);
	}

	return nullptr;
}