#include "SmartBombControl.h"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"
#include "Property.h"
#include "MissileChecker.h"

SmartBombControl::SmartBombControl()
{
	systemManager = nullptr;
	assetManager = nullptr;
}

SmartBombControl::SmartBombControl(SystemManager *s)
{
	systemManager = s;
	assetManager = nullptr;
}

SmartBombControl::~SmartBombControl()
{
}

void SmartBombControl::control(Entity *smartBomb, Entity *missile)
{
	MissileChecker *missileChecker = nullptr;
	sf::CircleShape* dodgeRadius = (smartBomb->getComponent("DodgeCircle")->getDataCircleShape().at(0));
	dodgeRadius->setPosition(smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0), smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1));

	//check for collision with outer bounding box.
	sf::Vector2f missilePoint(missile->getComponent("CurrentPosition")->getDataDouble().at(0), missile->getComponent("CurrentPosition")->getDataDouble().at(1));

	//Assumes it is called from missile checker.
	if ((smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0) - missile->getComponent("CurrentPosition")->getDataDouble().at(0)) > 0)
	{
		//move to the right.
		int tempYPosition = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1);
		int tempXPosition = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0);
		tempXPosition += abs(smartBomb->getComponent("Velocity")->getDataDouble().at(0));
		
		smartBomb->getComponent("CurrentPosition")->deleteData();
		smartBomb->getComponent("CurrentPosition")->addData(tempXPosition);
		smartBomb->getComponent("CurrentPosition")->addData(tempYPosition);
	}
	else
	{
		//move to the left
		int tempYPosition = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1);
		int tempXPosition = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0);
		tempXPosition -= abs(smartBomb->getComponent("Velocity")->getDataDouble().at(0));

		smartBomb->getComponent("CurrentPosition")->deleteData();
		smartBomb->getComponent("CurrentPosition")->addData(tempXPosition);
		smartBomb->getComponent("CurrentPosition")->addData(tempYPosition);
	}
}
