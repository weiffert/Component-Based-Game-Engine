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
	StateLoading(SystemManager *, AssetManager *);
	~StateLoading();
	void update(double, sf::RenderWindow *);

private:
	std::vector<std::string> filenames;
	std::vector<std::string> substrings;

	std::string fileDeterminer();
	void substringSorter();

	SystemManager* systemManager;
};


