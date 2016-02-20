#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateLevel :
	public BaseState
{

public:
	StateLevel(SystemManager*, AssetManager *);
	~StateLevel();
};

