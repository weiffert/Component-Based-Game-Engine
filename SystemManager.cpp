#include "stdafx.h"

#include <string>
#include <vector>

#include "SystemManager.h"
#include "Entity.h"
#include "BaseState.h"
#include "BaseController.h"
#include "BaseComponent.h"


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
  
  //Delete Controllers
  for(int i = 0; i < controller.size(); i++)
  {
  	delete controller.at(i);
  	controller.at(i) = nullptr;
  }
}


//Add to the vector of Entities.
//Takes in an Entity pointer.
void SystemManager::add(Entity* a)
{
	material.push_back(a);
}


//Add to the vector of BaseComponents.
//Takes in a BaseComponent pointer (a property).
void SystemManager::add(BaseComponent* a)
{
	component.push_back(a);
}


//Add to the vector of BaseControllers.
//Takes in a BaseController pointer (a controller).
void SystemManager::add(BaseController* a)
{
	controller.push_back(a);
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
			material.erase(search);
		}
	}
}


//Deletes a BaseComponent.
//Takes in a BaseComponent pointer (a property).
void SystemManager::remove(BaseComponent* a)
{
	for (int search = 0; search < component.size(); search++)
	{
		if (component.at(search)->getId() == a->getId())
		{
			//Remove the data.
			delete component.at(search);
			//Erase the pointer in the vector.
			component.erase(search);
		}
	}
}


//Deletes a BaseController.
//Takes in a BaseController pointer (a controller).
void SystemManager::remove(BaseController* a)
{
	for (int search = 0; search < controller.size(); search++)
	{
		if (controller.at(search)->getId() == a->getId())
		{
			//Remove the data.
			delete controller.at(search);
			//Erase the pointer in the vector.
			controller.erase(search);
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
			state.erase(search);
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
			material.erase(search);
		}
	}
}


//Delete a BaseComponent.
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
			component.erase(search);
		}
	}
}


//Delete a BaseController.
//Takes in the id.
void SystemManager::deleteController(std::string a)
{
	for (int search = 0; search < controller.size(); search++)
	{
		if (controller.at(search)->getId() == a)
		{
			//Remove the data.
			delete controller.at(search);
			//Erase the pointer in the vector.
			controller.erase(search);
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
			state.erase(search);
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
			state.erase(search);
		}
	}
}


//Returns a vector of entities that belong to the game state.
//Takes in a BaseState pointer (a game state).
std::vector<Entity*> SystemManager::getMaterial(BaseState* a)
{
	std::vector<Entity*> tempVector;
	//Checks if there is anything in the temporary vector.
	bool contentFlag = false;

	//Loops through all entities.
	for(int i = 0; i < material.size(); i++)
	{
		//Checks if it has a property that contains some form of state identification.
		if (material.at(i)->getProperty("stateNumber")->getData().at(0) == a->getNumber())
		{
			tempVector.push_back(material.at(i));
			contentFlag = true;
		}
		else if (material.at(i)->getProperty("stateId")->getData().at(0) == a->getId())
		{
			tempVector.push_back(material.at(i));
			contentFlag = true;
		}
	}

	//Checks if there is content.
	if (contentFlag)
		return tempVector;
	
	return nullptr;
}


//Returns the first Entity pointer with a matching id.
//Takes in an id string.
Entity * SystemManager::getMaterial(std::string a)
{
	//Loops through all entities.
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->getId() == a)
			return material.at(i);
	}

	return nullptr;
}


//Returns the first BaseComponent pointer with a matching id.
//Takes in an id string.
BaseComponent* SystemManager::getComponent(std::string a)
{
	//Loops through all properties.
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == a)
			return component.at(i);
	}

	return nullptr;
}


//Returns the first BaseController pointer with a matching id.
//Takes in an id string.
BaseController* SystemManager::getController(std::string a)
{
	//Loops through all controllers.
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i)->getId() == a)
			return controller.at(i);
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
