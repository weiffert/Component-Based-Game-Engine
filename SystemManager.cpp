#include "SystemManager.h"
#include <vector>


SystemManager::SystemManager()
{
}


SystemManager::~SystemManager()
{
  //Delete vectors
}


//Add a vector of entities.
void SystemManager::addMaterial(Entity* a)
{
	material.push_back(a);
}


//Add a BaseComponent.
void SystemManager::addComponent(BaseComponent* a)
{
	component.push_back(a);
}


//Add a BaseController.
void SystemManager::addController(BaseController* a)
{
	controller.push_back(a);
}


//Add a State.
void SystemManager::addState(BaseState* a)
{
	state.push_back(a);
}


//Delete an entity.
void SystemManager::deleteMaterial(string a)
{
	for (search = 0; search < material.size(); search++)
	{
		if (material.at(search)->getID == a)
		{
			delete *material.at(search);
			material.erase(search);
			search = material.size();
		}
	}
}


//Delete a BaseComponent.
void SystemManager::deleteComponent(string a)
{
	for (search = 0; search < component.size(); search++)
	{
		if (component.at(search)->getID == a)
		{
			delete *component.at(search);
			component.erase(search);
			search = component.size();
		}
	}
}


//Delete a BaseController.
void SystemManager::deleteController(string a)
{

	for (search = 0; search < controller.size(); search++)
	{
		if (controller.at(search)->getID == a)
		{
			delete *controller.at(search);
			controller.erase(search);
			search = controller.size();
		}
	}
}


/*
Need to make these handle int arguments instead of strings.
//Delete a BaseState.
void SystemManager::deleteState(string a)
{

	for (search = 0; search < state.size(); search++)
	{
		if (state.at(search)->getID == a)
		{
			delete *state.at(search);
			state.erase(search);
			search = component.size();
		}
	}
}


//Delete an entity.
void SystemManager::deleteMaterial(string a)
{
	for (search = 0; search < material.size(); search++)
	{
		if (material.at(search)->getID == a)
		{
			delete *material.at(search);
			material.erase(search);
			search = material.size();
		}
	}
}


//Delete a BaseComponent.
void SystemManager::deleteComponent(string a)
{
	for (search = 0; search < component.size(); search++)
	{
		if (component.at(search)->getID == a)
		{
			delete *component.at(search);
			component.erase(search);
			search = component.size();
		}
	}
}


//Delete a BaseController.
void SystemManager::deleteController(string a)
{

	for (search = 0; search < controller.size(); search++)
	{
		if (controller.at(search)->getID == a)
		{
			delete *controller.at(search);
			controller.erase(search);
			search = controller.size();
		}
	}
}


//Delete a BaseState.
void SystemManager::deleteState(string a)
{

	for (search = 0; search < state.size(); search++)
	{
		if (state.at(search)->getID == a)
		{
			delete *state.at(search);
			state.erase(search);
			search = component.size();
		}
	}
}
*/

//These need to handle exceptions. For instance, boundaries.
std::vector<Entity*> SystemManager::getMaterial(StateManager* a)
{
	//The following is not sufficient.
	return material.at(a.getNumber());
}


BaseComponent* SystemManager::getComponent(string a)
{

}


BaseController* SystemManager::getController(string a)
{

}


/*
These need to handle int arguments instead of string.s
//These need to handle exceptions. For instance, boundaries.
std::vector<Entity*> SystemManager::getMaterial(StateManager* a)
{
	//The following is not sufficient.
	return material.at(a.getNumber());
}


BaseComponent* SystemManager::getComponent(string a)
{

}


BaseController* SystemManager::getController(string a)
{

}

*/