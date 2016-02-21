#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateWelcome :
	public BaseState
{
public:
	StateWelcome(SystemManager *, AssetManager *);
	~StateWelcome();
};

