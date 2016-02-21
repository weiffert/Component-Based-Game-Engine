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
	StateEnd(SystemManager *, AssetManager *);
	~StateEnd();

private:
	std::vector<std::string> filenames;
	std::vector<std::string> substrings;

	std::string fileDeterminer();
	void substringSorter();
};

