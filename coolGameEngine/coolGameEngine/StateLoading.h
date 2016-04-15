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
	StateLoading();
	//Takes in Game's systemManager and assetManager.
	StateLoading(SystemManager *, AssetManager *);
	~StateLoading();

	//Update function. Overloads the pure virtual update function in BaseState.
	virtual std::string update(double, sf::RenderWindow *);

private:
	//Stores filenames.
	std::vector<std::string> filenames;
	//Stores strings of function determiners.
	std::vector<std::string> substrings;

	std::vector<Property *> entityProperties;
	std::vector<std::vector<std::string>> entityPropertiesData;

	//Determines the current file to read.
	std::string fileDeterminer();

	//Sorts the substrings into the proper usage order.
	void substringSorter();
	void initializeController(BaseController*, std::string, std::vector<std::string>);
	void initializeState(BaseState*, std::string, int);
};