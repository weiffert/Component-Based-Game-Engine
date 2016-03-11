#include "stdafx.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Render.h"
#include "Property.h"
#include "Entity.h"

Render::Render()
{

}


Render::~Render()
{

}


//Draws an entity to a window. It can only do one part of the entity.
//Takes in the lag between updates, window, and the entity to be drawn.
void Render::control(double lag, sf::RenderWindow *window, Entity *a)
{
	//Temp stores the property to be drawn.
	Property *temp, *temp2, *temp3;
	temp = nullptr;
	temp2 = nullptr;
	temp3 = nullptr;
	//Check if it can be drawn.
	if (a->hasComponent("draw"))
	{
		if (a->hasComponent("Sprite"))
		{
				temp = a->getComponent("Sprite");
				bool move = movement(lag, a, temp2, temp3);
				if (move)
					temp->getDataSprite().at(0).move(temp3->getDataDouble().at(0), temp3->getDataDouble().at(1));
				window->draw(temp->getDataSprite().at(0));
		}
		else if (a->hasComponent("Text"))
		{
			temp = a->getComponent("Text");
			bool move = movement(lag, a, temp2, temp3);
			if (move)
				temp->getDataSprite().at(0).move(temp3->getDataDouble().at(0), temp3->getDataDouble().at(1));
			window->draw(temp->getDataSprite().at(0));
		}
		else if (a->hasComponent("Shape"))
		{
			temp = a->getComponent("Shape");
			bool move = movement(lag, a, temp2, temp3);
			if (move)
				temp->getDataSprite().at(0).move(temp3->getDataDouble().at(0), temp3->getDataDouble().at(1));
			window->draw(temp->getDataSprite().at(0));
		}
	}
}


bool Render::movement(double lag, Entity* a, Property* temp2, Property* temp3)
{
	//Update position based on time lag.
	double speed, x, y, changeX, changeY;
	if (a->hasComponent("velocity"))
	{
		//Holds the velocity.
		temp2 = a->getComponent("velocity");

		if (a->hasComponent("position"))
		{
			//Holds the current position.
			temp3 = a->getComponent("position");

			//Update Position.
			//speed * lag = distance.
			x = temp3->getDataDouble().at(0);
			y = temp3->getDataDouble().at(1);
			changeX = temp2->getDataDouble().at(0) * lag;
			changeY = temp2->getDataDouble().at(1) * lag;

			//Store new position.
			temp3->changeData(changeX + x, 0);
			temp3->changeData(changeY + y, 1);

			return true;
		}
	}
	return false;
}