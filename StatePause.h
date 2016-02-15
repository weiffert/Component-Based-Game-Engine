#pragma once
#include "BaseState.h"
#include "SystemManager.h"

class StatePause :
	public BaseState
{
public:
	StatePause(SystemManager *);
	~StatePause();
};

