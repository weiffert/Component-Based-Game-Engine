#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateEnd :
	public BaseState
{
public:
	StateEnd(SystemManager *, AssetManager *);
	~StateEnd();
};

