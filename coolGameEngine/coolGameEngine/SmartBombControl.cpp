#include "SmartBombControl.h"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"
#include "MissileChecker.h"

SmartBombControl::SmartBombControl()
{
	systemManager = nullptr;
	assetManager = nullptr;
}

SmartBombControl::SmartBombControl(SystemManager *s, AssetManager *a)
{
	systemManager = s;
	assetManager = a;
}

SmartBombControl::~SmartBombControl()
{
}

void SmartBombControl::control(Entity *e)
{
	Property *p = e->getComponent("DodgeCircle");
	//check for explosion collision with outer bounding box.
	//If 0, don't do anything.
	//If -1, it means its to the left. Move right.
	//If 1, its to the right. Move left.
	//Move in the opposite direction.
}
