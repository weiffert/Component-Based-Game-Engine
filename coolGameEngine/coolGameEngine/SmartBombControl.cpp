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

void SmartBombControl::control(Entity *smartBomb, Entity *missile)
{
        MissileChecker *missileChecker;
        SystemManager *systemManager;
        sf::CircleShape *dodgeRadius = smartBomb->getComponent("DodgeCircle")->getDataCircleShape().at(0);
	dodgeRadius.setPosition(smartBomb->getComponenet("CurrentPosition")->getDataDouble().at(0), smartBomb->getComponenet("CurrentPosition")->getDataDouble().at(1));

	//check for collision with outer bounding box.

        if(missileChecker.intersection(dodgeRadius, sf::Vector2f(missile->getComponent("CurrentPosition")->getDataDouble.at(0), 

	//If 0, don't do anything.
	//If -1, it means its to the left. Move right.
	//If 1, its to the right. Move left.
	//Move in the opposite direction.
}
