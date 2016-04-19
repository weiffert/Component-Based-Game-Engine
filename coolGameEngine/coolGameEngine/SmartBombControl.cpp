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
	MissileChecker *missileChecker = nullptr;
	sf::CircleShape* dodgeRadius = (smartBomb->getComponent("DodgeCircle")->getDataCircleShape().at(0));
	dodgeRadius->setPosition(smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0), smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1));

	//check for collision with outer bounding box.
    sf::Vector2f missilePoint(missile->getComponent("CurrentPosition")->getDataDouble().at(0), missile->getComponent("CurrentPosition")->getDataDouble().at(1));

	if (missileChecker->intersection(*dodgeRadius, missilePoint) == true)
    {
		if((smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0) - missile->getComponent("CurrentPosition")->getDataDouble().at(0)) > 0)
		{
			//move to the right
            int tempYPosition = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1);
            int tempXPosition = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0);
            tempXPosition += 1;

            smartBomb->getComponent("CurrentPosition")->deleteData();
            smartBomb->getComponent("CurrentPosition")->addData(tempYPosition);
            smartBomb->getComponent("CurrentPosition")->addData(tempXPosition);
         }
         else
         {
             //move to the left
             int tempYPosition = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1);
             int tempXPosition = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0);
             tempXPosition -= 1;

             smartBomb->getComponent("CurrentPosition")->deleteData();
             smartBomb->getComponent("CurrentPosition")->addData(tempYPosition);
             smartBomb->getComponent("CurrentPosition")->addData(tempXPosition);
         }
    } 
}
