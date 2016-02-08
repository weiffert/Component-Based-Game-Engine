#pragma once
#include <string>
#include <vector>
#include "BaseComponent.h"
#include "BaseController.h"


class Entity
{
private:
	std::string id;
	std::vector<BaseComponent*> components;
	std::vector<BaseController*> controllers;

public:
	Entity();
	~Entity();
	std::string getId();
	void setId(std::string);

	void addComponent(BaseComponent*);
	void removeComponent();
	BaseComponent* getComponent();
	bool hasComponent();

	void addController(BaseController*);
	void removeController();
	BaseController* getController();
	bool hasController();
};
