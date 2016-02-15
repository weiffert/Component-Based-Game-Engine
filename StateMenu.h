#pragma once
#include "BaseState.h"
#include "SystemManager.h"
class StateMenu :
	public BaseState
{
public:
	StateMenu(SystemManager *);
	~StateMenu();
};

