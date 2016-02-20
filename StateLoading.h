#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include <string.h>

class StateLoading :
	public BaseState
{
public:
	StateLoading(SystemManager *, AssetManager *);
	~StateLoading();

private:
	std::vector<std::string> filenames;
	std::vector<std::string> substrings;

	std::string fileDeterminer();
	void substringSorter();
};


