#pragma once
#include <string>
#include <vector>


class SystemManager
{
public:
	SystemManager();
	~SystemManager();
	void addMaterial(Entity*, StateManager*);
	void addComponent();
	void addController();
	void addState(BaseState*);
	void deleteMaterial(string);
	void deleteComponent(string);
	void deleteController(string);
	void deleteState(string);
	Entity* getMaterial(string);
	std::vector<Entity*> getMaterial(StateManager*);
	BaseComponent* getComponent(string);
	BaseController* getController(string);
	BaseState* getState(string);
	
private:
	std::vector<vector<Entity*>> material;
	std::vector<BaseComponent*> component;
	std::vector<BaseController*> controller;
	std::vector<BaseState*> state(6); //Make size 6 so that it is easier in the constructor
};
