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
	BaseState();
	~BaseState();

	//Returns the state identification.
	int getNumber();
	std::string getId();

	//Set the state identification
	void setId(std::string);
	void setNumber(int);

	//Set the entities contained in the state.
	void setMaterial(std::vector<Entity*>);

	//Render a state.
	void render(double, sf::RenderWindow *);

	//Update function.
	virtual void update(double, sf::RenderWindow *) = 0;

protected:
	int number;
	std::string id;
	std::vector<Entity*> material;
	SystemManager* systemManager;
	AssetManager* assetManager;

	//Change the current state.
	void changeState(BaseState *);
	void changeState(BaseState *, std::string);
	void changeState(BaseState *, int);
};
