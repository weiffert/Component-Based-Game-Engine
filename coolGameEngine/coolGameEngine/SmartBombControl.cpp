#include "SmartBombControl.h"

#include <math.h>
#include <iostream>

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
		double velocity = smartBomb->getComponent("Velocity")->getDataDouble().at(0);
		if (velocity <= 0)
		{
			smartBomb->getComponent("BeenMoved")->deleteData();
			smartBomb->getComponent("BeenMoved")->addData(true);
			
			double theta = atan((smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1) - smartBomb->getComponent("ExplodingPosition")->getDataDouble().at(1)) / (smartBomb->getComponent("ExplodingPosition")->getDataDouble().at(0) - smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0)));
			theta *= -1;
			double lengthX = -1 * velocity * cos(theta);
			double lengthY = -1 * velocity * sin(theta); 
			
			double changeX = cos(theta);
			double changeY = sin(theta);

			double temp1 = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0) + lengthX;
			double temp2 = (changeY / changeX) * (temp1 - smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0)) + -1 * smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1);
			temp2 *= -1;

			smartBomb->getComponent("Velocity")->deleteData();
			smartBomb->getComponent("Velocity")->addData(velocity);
			smartBomb->getComponent("Velocity")->addData(lengthX);
			smartBomb->getComponent("Velocity")->addData(lengthY);

			smartBomb->getComponent("CurrentPosition")->deleteData();
			smartBomb->getComponent("CurrentPosition")->addData(temp1);
			smartBomb->getComponent("CurrentPosition")->addData(temp2);


			sf::Sprite *s = smartBomb->getComponent("Sprite")->getDataSprite().at(0);
			s->setPosition(temp1, temp2);
		}
	}
	else
	{
		//move to the left
		double velocity = smartBomb->getComponent("Velocity")->getDataDouble().at(0);
		if (velocity >= 0)
		{
			smartBomb->getComponent("BeenMoved")->deleteData();
			smartBomb->getComponent("BeenMoved")->addData(true);

			double theta = atan((smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1) - smartBomb->getComponent("ExplodingPosition")->getDataDouble().at(1)) / (smartBomb->getComponent("ExplodingPosition")->getDataDouble().at(0) - smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0)));
			theta *= -1;
			double lengthX = -1 * velocity * cos(theta);
			double lengthY = -1 *  velocity * sin(theta);

			double changeX = cos(theta);
			double changeY = sin(theta);

			double temp1 = smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0) + lengthX;
			double temp2 = (changeY / changeX) * (temp1 - smartBomb->getComponent("CurrentPosition")->getDataDouble().at(0)) + -1 * smartBomb->getComponent("CurrentPosition")->getDataDouble().at(1);
			temp2 *= -1;

			smartBomb->getComponent("Velocity")->deleteData();
			smartBomb->getComponent("Velocity")->addData(velocity);
			smartBomb->getComponent("Velocity")->addData(lengthX);
			smartBomb->getComponent("Velocity")->addData(lengthY);

			smartBomb->getComponent("CurrentPosition")->deleteData();
			smartBomb->getComponent("CurrentPosition")->addData(temp1);
			smartBomb->getComponent("CurrentPosition")->addData(temp2);


			sf::Sprite *s = smartBomb->getComponent("Sprite")->getDataSprite().at(0);
			s->setPosition(temp1, temp2);
		}
	}
}
