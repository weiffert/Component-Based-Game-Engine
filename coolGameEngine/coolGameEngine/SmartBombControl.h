#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"

class SmartBombControl
{
public: 
	SmartBombControl();
	SmartBombControl(SystemManager*);
	~SmartBombControl();
	void control(Entity *, Entity *);
private:
	SystemManager *systemManager;
	AssetManager *assetManager;
};
