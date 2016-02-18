#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "SystemManager.h"
//SFML Includes

class BaseState
{
public:
	BaseState(SystemManager *);
	~BaseState();
	int getNumber();
	std::string getId();
	void setId(std::string);

	virtual void update() = 0;
	virtual void render(double, sf::RenderWindow) = 0;

protected:
	int number;
	std::vector<Entity*> material;
	std::string id;
	SystemManager *systemMananger;
};
