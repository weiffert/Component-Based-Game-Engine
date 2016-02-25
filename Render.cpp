#include "stdafx.h"

#include "Render.h"

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
	bool drawable = false;
	//Temp stores the property to be drawn.
	BaseComponent *temp, *temp2, *temp3;

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
			x = temp3->getData(0);
			y = temp3->getData(1);
			changeX = temp2->getData(0) * lag;
			changeY = temp2->getData(1) * lag;

			//Store new position.
			temp3->changeData(changeX + x, 0);
			temp3->changeData(changeY + y, 1);
		}
	}

	//Check if it can be drawn.
	if (a->hasComponent("draw"))
	{
		if (a->hasComponent("Sprite"))
		{
			if (a->hasComponent("Image"))
			{
				drawable = true;
				temp = a->getComponent("Sprite");
			}
			if (a->hasComponent("Texture"))
			{
				drawable = true;
				temp = a->getComponent("Sprite");
			}
		}
		else if (a->hasComponent("Text"))
		{
			drawable = true;
			temp = a->getComponent("Text");
		}
		else if (a->hasComponent("VertexArray"))
		{
			drawable = true;
			temp = a->getComponent("VertexArray");
		}
		else if (a->hasComponent("Shape"))
		{
			drawable = true;
			temp = a->getComponent("Shape");
		}

		//If it can be drawn, draw the drawable property.
		if (drawable)
		{
			temp->move(temp3->getData(0), temp3->getData(1));
			window->draw(temp);
		}
	}
}