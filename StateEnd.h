#pragma once
#include "BaseState.h"
#include "SystemManager.h"

class StateEnd :
	public BaseState
{
public:
	StateEnd(SystemManager *);
	~StateEnd();
};

