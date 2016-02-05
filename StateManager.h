#pragma once
#include <string>
#include <vector>
#include "Entity.h"

class StateManager
{
public:
	StateManager();
	~StateManager();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual const int getNumber() = 0;
	virtual const std::string getId() = 0;
private:
	std::vector<Entity*> material;
	std::vector<sf::Image*> assetImage;
	std::vector<sf::Sound*> assetSound;
protected:
	std::string id;
	int number;
};

