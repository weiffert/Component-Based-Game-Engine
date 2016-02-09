#pragma once
#include "BaseState.h"
#include <string>

class StateLoading : public BaseState
{
private:
	//Maybe move these to constructor
	int number;
	std::string id;

public:

	StateLoading();
	~StateLoading();

};
