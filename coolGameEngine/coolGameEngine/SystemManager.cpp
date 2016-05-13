#include "stdafx.h"

#include <string>
#include <vector>
#include <iostream>

#include "SystemManager.h"
#include "Entity.h"
#include "BaseState.h"
#include "Property.h"


SystemManager::SystemManager()
{
}


//Deletes the data in the vectors off of the heap.
SystemManager::~SystemManager()
{
  //Delete states
  for(int i = 0; i < state.size(); i++)
  {
  	delete state.at(i);
  	state.at(i) = nullptr;
  }
  
  //Delete Entities
  for (int i = 0; i < material.size(); i++)
  {
  	delete material.at(i);
  	material.at(i) = nullptr;
  }
  
  //Delete Components
  for(int i = 0; i < component.size(); i++)
  {
  	delete component.at(i);
  	component.at(i) = nullptr;
  }
}


//Add to the vector of Entities.
//Takes in an Entity pointer.
void SystemManager::add(Entity* a)
{
	material.push_back(a);
}


//Add to the vector of Propertys.
//Takes in a Property pointer (a property).
void SystemManager::add(Property* a)
{
	component.push_back(a);
}


//Add to the vector of States.
//Takes in a BaseState pointer (a game state).
void SystemManager::add(BaseState* a)
{
	state.push_back(a);
}


//Deletes an Entity.
//Takes in an Entity pointer.
void SystemManager::remove(Entity* a)
{
	for (int search = 0; search < material.size(); search++)
	{
		if (material.at(search)->getId() == a->getId())
		{
			//Remove the data.
			delete material.at(search);
			//Erase the pointer in the vector.
			material.erase(material.begin() + search);
		}
	}
}


//Deletes a Property.
//Takes in a Property pointer (a property).
void SystemManager::remove(Property* a)
{
	for (int search = 0; search < component.size(); search++)
	{
		if (component.at(search)->getId() == a->getId())
		{
			//Remove the data.
			delete component.at(search);
			//Erase the pointer in the vector.
			component.erase(component.begin() + search);
		}
	}
}


//Deletes a BaseState.
//Takes in a BaseState pointer (a game state).
void SystemManager::remove(BaseState* a)
{
	for (int search = 0; search < state.size(); search++)
	{
		if (state.at(search)->getId() == a->getId())
		{
			//Remove the data.
			delete state.at(search);
			//Erase the pointer in the vector.
			state.erase(state.begin() + search);
		}
	}
}


//Delete an Entity.
//Takes in the id.
void SystemManager::deleteMaterial(std::string a)
{
	for (int search = 0; search < material.size(); search++)
	{
		if (material.at(search)->getId() == a)
		{
			//Remove the data.
			delete material.at(search);
			//Erase the pointer in the vector.
			material.erase(material.begin() + search);
		}
	}
}


//Delete a Property.
//Takes in the id.
void SystemManager::deleteComponent(std::string a)
{
	for (int search = 0; search < component.size(); search++)
	{
		if (component.at(search)->getId() == a)
		{
			//Remove the data.
			delete component.at(search);
			//Erase the pointer in the vector.
			component.erase(component.begin() + search);
		}
	}
}


//Delete a BaseState.
//Takes in the id.
void SystemManager::deleteState(std::string a)
{
	for (int search = 0; search < state.size(); search++)
	{
		if (state.at(search)->getId() == a)
		{
			//Remove the data.
			delete state.at(search);
			//Erase the pointer in the vector.
			state.erase(state.begin() + search);
		}
	}
}


//Delete a BaseState.
//Takes in the id number.
void SystemManager::deleteState(int a)
{
	for (int search = 0; search < state.size(); search++)
	{
		if (state.at(search)->getNumber() == a)
		{
			//Remove the data.
			delete state.at(search);
			//Erase the pointer in the vector.
			state.erase(state.begin()+search);
		}
	}
}


//Returns a vector of entities that belong to the game state.
//Takes in a BaseState pointer (a game state).
std::vector<Entity*> SystemManager::getMaterial(BaseState* a)
{
	std::vector<Entity*> tempVector;

	//Loops through all entities.
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->getComponent("StateId"))
		{
			if (material.at(i)->getComponent("StateId")->getDataString().at(0) == a->getId())
				tempVector.push_back(material.at(i));
		}
		//Checks if it has a property that contains some form of state identification.
		else if (material.at(i)->getComponent("StateNumber"))
		{
			if (material.at(i)->getComponent("StateNumber")->getDataInt().at(0) == a->getNumber())
				tempVector.push_back(material.at(i));
		}
	}
	return tempVector;
}


//Returns the first Entity pointer with a matching id.
//Takes in an id string.
Entity* SystemManager::getMaterial(std::string a)
{
	//Loops through all entities.
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->getId() == a)
			return material.at(i);
	}

	return nullptr;
}


//Returns the first Property pointer with a matching id.
//Takes in an id string.
Property* SystemManager::getComponent(std::string a)
{
	//Loops through all properties.
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == a)
			return component.at(i);
	}

	return nullptr;
}


//Returns the first BaseState pointer with a matching id.
//Takes in an id string.
BaseState* SystemManager::getState(std::string a)
{
	//Loops through all game states.
	for (int i = 0; i < state.size(); i++)
	{
		if (state.at(i)->getId() == a)
			return state.at(i);
	}

	return nullptr;
}


//Returns the first BaseController pointer with a matching id.
//Takes in an id int.
BaseState* SystemManager::getState(int a)
{
	//Loops through all game states.
	for (int i = 0; i < state.size(); i++)
	{
		if (state.at(i)->getNumber() == a)
			return state.at(i);
	}

	return nullptr;
}
