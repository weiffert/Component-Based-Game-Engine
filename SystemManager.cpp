#include "stdafx.h"
#include "SystemManager.h"
#include <vector>


SystemManager::SystemManager()
{
}


SystemManager::~SystemManager()
{
  //Delete states
  for(int i = 0; i < state.size(); i++)
  {
  	delete state.at(i);
  	state.at(i) = nullptr;
  }
  
  //Delete Entities
  for(int i = 0 i < material.size(); i++)
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


//Add a vector of entities.
void SystemManager::add(Entity* a)
{
	material.push_back(a);
}


//Add a BaseComponent.
void SystemManager::add(BaseComponent* a)
{
	component.push_back(a);
}


//Add a BaseController.
void SystemManager::add(BaseController* a)
{
	controller.push_back(a);
}


//Add a State.
void SystemManager::add(BaseState* a)
{
	state.push_back(a);
}


//The removes are standard.
//Deletes an Entity. 
void SystemManager::remove(Entity* a)
{
	for (search = 0; search < material.size(); search++)
	{
		if (material.at(search)->getID == a)
		{
			delete *material.at(search);
			material.erase(search);
		}
	}
}


//Deletes a BaseComponent
void SystemManager::remove(BaseComponent* a)
{
	for (search = 0; search < component.size(); search++)
	{
		if (component.at(search)->getID == a)
		{
			delete *component.at(search);
			component.erase(search);
		}
	}
}


//Deletes a BaseController
void SystemManager::remove(BaseController* a)
{
	for (search = 0; search < controller.size(); search++)
	{
		if (controller.at(search)->getID == a)
		{
			delete *controller.at(search);
			controller.erase(search);
		}
	}
}


//Deletes a BaseState
void SystemManager::remove(BaseState* a)
{
	for (search = 0; search < state.size(); search++)
	{
		if (state.at(search) == a)
			delete *state.at(search);
	}
}


//These are only for cases where all the program has is the string or int.
//Delete an entity.
void SystemManager::deleteMaterial(std::string a)
{
	for (search = 0; search < material.size(); search++)
	{
		if (material.at(search)->getID == a)
		{
			delete *material.at(search);
			material.erase(search);
		}
	}
}


//Delete a BaseComponent.
void SystemManager::deleteComponent(std::string a)
{
	for (search = 0; search < component.size(); search++)
	{
		if (component.at(search)->getID == a)
		{
			delete *component.at(search);
			component.erase(search);
		}
	}
}


//Delete a BaseController.
void SystemManager::deleteController(std::string a)
{
	for (search = 0; search < controller.size(); search++)
	{
		if (controller.at(search)->getID == a)
		{
			delete *controller.at(search);
			controller.erase(search);
		}
	}
}


//Delete a BaseState.
void SystemManager::deleteState(std::string a)
{

	for (search = 0; search < state.size(); search++)
	{
		if (state.at(search)->getId == a)
		{
			delete *state.at(search);
			state.erase(search);
		}
	}
}


//Delete a BaseState.
void SystemManager::deleteState(int a)
{

	for (search = 0; search < state.size(); search++)
	{
		if (state.at(search)->getNumber == a)
		{
			delete *state.at(search);
			state.erase(search);
		}
	}
}


//Returns a vector of entities that belong to the state.
std::vector<Entity*> SystemManager::getMaterial(BaseState* a)
{
	vector<Entity*> tempVector;
	bool contentFlag = false;
	for(int i = 0; i < material.size(); i++)
	{
		if (materal.at(i)->getProperty("stateNumber")->getData().at(0) == a->getNumber())
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
	if (contentFlag)
		return tempVector;
	
	return nullptr;
}


//Returns an entity.
Entity * SystemManager::getMaterial(std::string a)
{
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->getId() == a)
			return material.at(i);
	}

	return nullptr;
}


//Returns a component with the same id.
BaseComponent* SystemManager::getComponent(std::string a)
{
	for (int i = 0; i < component.size(); i++)
	{
		if (component.at(i)->getId() == a)
			return component.at(i);
	}

	return nullptr;
}


//Returns a controller with the same id.
BaseController* SystemManager::getController(std::string a)
{
	for (int i = 0; i < controller.size(); i++)
	{
		if (controller.at(i)->getId() == a)
			return controller.at(i);
	}

	return nullptr;
}


//Returns a state with the same id.
BaseState* SystemManager::getState(std::string a)
{
	for (int i = 0; i < states.size(); i++)
	{
		if (states.at(i)->getId() == a)
			return states.at(i);
	}

	return nullptr;
}


//Returns a state with the same number id.
BaseState* SystemManager::getState(int a)
{
	for (int i = 0; i < states.size(); i++)
	{
		if (states.at(i)->getNumber() == a)
			return states.at(i);
	}

	return nullptr;
}