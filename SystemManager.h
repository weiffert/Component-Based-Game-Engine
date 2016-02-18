#pragma once
#include <string>
#include <vector>


class SystemManager
{
public:
	SystemManager();
	~SystemManager();
	void addMaterial(Entity*);
	void addComponent(BaseComponent *);
	void addController(BaseController *);
	void addState(BaseState*);
	void deleteMaterial(std::string);
	void deleteComponent(std::string);
	void deleteController(std::string);
	void deleteState(std::string);
	void deleteState(int);
	Entity* getMaterial(std::string);
	std::vector<Entity*> getMaterial(StateManager*);
	BaseComponent* getComponent(std::string);
	BaseController* getController(std::string);
	BaseState* getState(std::string);
	BaseState* getState(int);
	
private:
	std::vector<Entity*> material;
	std::vector<BaseComponent*> component;
	std::vector<BaseController*> controller;
	std::vector<BaseState*> state;
};
