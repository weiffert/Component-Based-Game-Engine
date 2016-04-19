#pragma once

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"

class SmartBombControl
{
public: 
	SmartBombControl();
	SmartBombControl(SystemManager*, AssetManager*);
	~SmartBombControl();
	void control(Entity *, Entity *);
private:
	SystemManager *systemManager;
	AssetManager *assetManager;
};
