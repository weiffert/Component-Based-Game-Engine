#pragma once
#include <string>
#include <vector>

#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateLoading :
	public BaseState
{
public:
	//Takes in Game's systemManager and assetManager.
	StateLoading(SystemManager *, AssetManager *);
	~StateLoading();

	//Update function. Overloads the pure virtual update function in BaseState.
	virtual void update(double, sf::RenderWindow *);

private:
	//Stores filenames.
	std::vector<std::string> filenames;
	//Stores strings of function determiners.
	std::vector<std::string> substrings;

	//Determines the current file to read.
	std::string fileDeterminer();

	//Sorts the substrings into the proper usage order.
	void substringSorter();
}


