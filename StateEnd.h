#pragma once
#include <vector>
#include <string>

#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateEnd :
	public BaseState
{
public:
	//Takes in Game's systemManager and assetManager.
	StateEnd(SystemManager *, AssetManager *);
	~StateEnd();

	//Update function. Overloads the pure virtual update function in BaseState.
	void update(double, sf::RenderWindow*);

private:
	//Stores filenames.
	std::vector<std::string> filenames;
	//Stores strings of function determiners.
	std::vector<std::string> substrings;

	//Determines the current file to read.
	std::string fileDeterminer();

	//Sorts the substrings into the proper usage order.
	void substringSorter();

	//This should be in BaseState.
	SystemManager* systemManager;
};

