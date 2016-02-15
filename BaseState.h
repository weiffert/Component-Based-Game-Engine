#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "SystemManager.h"

class BaseState
{
public:
	BaseState(SystemManager *);
	~BaseState();
	virtual void update() = 0;
	virtual void render() = 0;
	int getNumber();
	std::string getId();
protected:
	std::vector<Entity*> material;
	std::string id;
	int number;
	SystemManager *systemMananger;
};
