#pragma once
#include <string>
#include <vector>


class SystemManager
{
public:
	SystemManager();
	~SystemManager();
	void add(Entity*);
	void add(BaseComponent *);
	void add(BaseController *);
	void add(BaseState*);
	void remove(Entity*);
	void remove(BaseComponent*);
	void remove(BaseController*);
	void remove(BaseState*);
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
