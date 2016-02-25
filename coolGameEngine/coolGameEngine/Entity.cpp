#include "stdafx.h"

#include <string>
#include <vector>

#include "Entity.h"
#include "BaseComponent.h"
#include "BaseController.h"


Entity::Entity()
{
	//Set Defaults.
	id = "Entity";
}


Entity::~Entity()
{

}


//Returns the entity's id.
std::string Entity::getId()
{
	return id;
}


//Sets the id.
void Entity::setId(std::string newId)
{
	id = newId;
}


//Add to the component vector.
//Takes in a BaseComponent pointer (a property).
void Entity::add(BaseComponent* newComponent)
{
	component.push_back(newComponent);
}


//Add to the controller vector.
//Takes in a BaseController pointer (a controller).
void Entity::add(BaseController* newComponent)
{
	controller.push_back(newComponent);
}


//Delete a BaseComponent.
//Takes in the BaseComponent to be deleted.
void Entity::remove(BaseComponent *a)
{
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == a->getId())
		{
			//Remove the data.
			delete component.at(i);
			//Erase the pointer from the vector.
			component.erase(component.begin()+i);
		}
	}
}


//Delete a BaseController.
//Takes in the BaseController to be deleted.
void Entity::remove(BaseController *a)
{
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i)->getId() == a->getId())
		{
			//Remove the data.
			delete controller.at(i);
			//Erase the pointer from the vector.
			controller.erase(controller.begin()+i);
		}
	}
}


//Delete a BaseComponent.
//Takes in the BaseComponent id string to be deleted.
void Entity::deleteComponent(std::string id)
{
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == id)
		{
			//Remove the data.
			delete component.at(i);
			//Erase the pointer from the vector.
			component.erase(component.begin() + i);
		}
	}
}


//Delete a BaseController.
//Takes in the BaseController id string to be deleted.
void Entity::deleteController(std::string id)
{
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i)->getId() == id)
		{
			//Remove the data.
			delete controller.at(i);
			//Erase the pointer from the vector.
			controller.erase(controller.begin() + i);
		}
	}
}


//Checks if the entity has a particular property.
//Takes in the BaseComponent id.
//Returns true or false.
bool Entity::hasComponent(std::string id)
{
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == id)
			return true;
	}

	return false;
}


//Checks if the entity has a particular controller.
//Takes in the BaseController id.
//Returns true or false.
bool Entity::hasController(std::string id)
{
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i)->getId() == id)
			return true;
	}
	
	return false;
}


//Checks if the entity has a particular property.
//Takes in the BaseComponent id.
//Returns the BaseComponent.
BaseComponent* Entity::getComponent(std::string id)
{
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == id)
			return component.at(i);
	}

	return nullptr;
}


//Checks if the entity has a particular controller.
//Takes in the BaseController id.
//Returns the BaseController.
BaseController* Entity::getController(std::string id)
{
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i)->getId() == id)
			return controller.at(i);
	}

	return nullptr;
}