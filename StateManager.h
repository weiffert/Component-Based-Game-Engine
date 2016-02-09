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
	virtual int getNumber() = 0;
	virtual std::string getId() = 0;
	void changeState(int);
	void changeState(std::string);
private:
	std::vector<Entity*> material;
	std::vector<sf::Image*> assetImage;
	std::vector<sf::Sound*> assetSound;
	std::string id;
	int number;
};
