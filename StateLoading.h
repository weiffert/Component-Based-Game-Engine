#pragma once
#include "BaseState.h"
#include "SystemManager.h"
class StateLoading :
	public BaseState
{
public:
	StateLoading(*SystemManager);
	~StateLoading();
	
private:
	SystemManager systemManager;
};


