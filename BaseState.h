#pragma once
#include <string>
#include <vector>

#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "Entity.h"
#include "SystemManager.h"
#include "AssetManager.h"

class BaseState
{
public:
	BaseState(SystemManager *, AssetManager *);
	~BaseState();
	int getNumber();
	std::string getId();
	void setId(std::string);
	void setNumber(int);
	void setMaterial(std::vector<Entity*>);

	virtual void update(double, sf::RenderWindow) = 0;
	virtual void render(double, sf::RenderWindow) = 0;

protected:
	int number;
	std::vector<Entity*> material;
	std::string id;
	SystemManager* systemMananger;
	AssetManager *assetManager;

	void changeState(BaseState *);
	void changeState(BaseState *, std::string);
	void changeState(BaseState *, int);
};
