#pragma once
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"

class StateMenu :
	public BaseState
{

public:
	StateMenu(SystemManager *, AssetManager *);
	~StateMenu();
};

