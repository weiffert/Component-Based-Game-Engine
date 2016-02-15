#pragma once
#include "BaseState.h"
#include "SystemManager.h"
class StateWelcome :
	public BaseState
{
public:
	StateWelcome(SystemManager *);
	~StateWelcome();
};

