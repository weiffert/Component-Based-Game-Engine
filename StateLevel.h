#pragma once
#include "BaseState.h"
#include "SystemManager.h"

class StateLevel :
	public BaseState
{
public:
	StateLevel(SystemManger *);
	~StateLevel();
};

