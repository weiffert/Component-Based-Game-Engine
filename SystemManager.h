#pragma once
#include <string>
#include <vector>


class SystemManager
{
public:
	SystemManager();
	~SystemManager();
	void addMaterial();
	void addComponent();
	void addController();
	std::vector<Entity*> getMaterial();
	std::vector<BaseComponent*> getComponent();
	std::vector<BaseController*> getController();
	
	
private:
	std::vector<vector<Entity*>> material;
	std::vector<BaseComponent*> component;
	std::vector<BaseController*> controller;
};
