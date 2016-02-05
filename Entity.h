#pragma once
#include <string>
#include "vector"
#include "BaseComponent"
#include "BaseController"
class Entity
{
private:
	const string id;
	std::vector<BaseComponent*> components;
	std::vector<BaseController*> controllers;

public:
	string getId();
	string setId(string);

	void addComponent(*BaseComponent);
	void removeComponent();
	*BaseComponent getComponent();
	bool hasComponent();

	void addController(*BaseController);
	void removeController();
	*BaseController getController();
	bool hasCOntroller();
};