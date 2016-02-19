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

private:
	vector<std::string> filenames;
	vector<std::string> substrings;
	int iteration;

	std::string fileDeterminer();
	void substringSorter();
};


