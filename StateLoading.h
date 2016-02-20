#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include <string.h>

class StateLoading :
	public BaseState
{
public:
	StateLoading(SystemManager *);
	~StateLoading();

	int loadingUpdate(double);
	void render(double, sf::RenderWindow);

protected:
	std::vector<std::string> filenames;
	std::vector<std::string> substrings;
	int iteration;

	SystemManager* systemManager;

	std::string fileDeterminer();
	void substringSorter();
};


