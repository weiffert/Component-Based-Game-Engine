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
        sf::CircleShape *dodgeRadius = e->getComponent("DodgeCircle")->getDataCircleShape().at(0);
	dodgeRadius.setPosition(e->getComponenet("CurrentPosition")->getDataDouble().at(0), e->getComponenet("CurrentPosition")->getDataDouble().at(1));

	//check for collision with outer bounding box.

        if(
	//If 0, don't do anything.
	//If -1, it means its to the left. Move right.
	//If 1, its to the right. Move left.
	//Move in the opposite direction.
}
