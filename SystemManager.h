#pragma once
#include <string>
#include <vector>

#include "Entity.h"
#include "BaseState.h"
#include "BaseController.h"
#include "BaseComponent.h"


class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	//Adds to the proper vector
	void add(Entity*);
	void add(BaseComponent *);
	void add(BaseController *);
	void add(BaseState*);

	//Removes from the proper vector. It is erased permanently.
	void remove(Entity*);
	void remove(BaseComponent*);
	void remove(BaseController*);
	void remove(BaseState*);

	//Removes from the proper vector using the id. It is erased permanently.
	void deleteMaterial(std::string);
	void deleteComponent(std::string);
	void deleteController(std::string);
	void deleteState(std::string);
	void deleteState(int);

	//Returns the proper class based off of the id.
	Entity* getMaterial(std::string);
	BaseComponent* getComponent(std::string);
	BaseController* getController(std::string);
	BaseState* getState(std::string);
	BaseState* getState(int);

	//Returns a vector of entities based on the state.
	std::vector<Entity*> getMaterial(BaseState*);

private:
	//Stores the system's stuff.
	std::vector<Entity*> material;
	std::vector<BaseComponent*> component;
	std::vector<BaseController*> controller;
	std::vector<BaseState*> state;
};
