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
	control(Entity *);
private:
	SystemManager *systemManager;
	AssetManager *assetManager;
}
