#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StatePause :
	public BaseState
{

public:
	StatePause(SystemManager *, AssetManager *);
	~StatePause();
};

