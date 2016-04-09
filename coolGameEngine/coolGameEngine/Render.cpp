#include "stdafx.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Render.h"
#include "Property.h"
#include "Entity.h"

#include <iostream>

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
	window->clear();

	//Temp stores the property to be drawn.
	Property *temp;
	temp = nullptr;
	int *x = 0, *y = 0;
	//Check if it can be drawn.
	if (a->hasComponent("Sprite"))
	{
		temp = a->getComponent("Sprite");
		/*sf::Texture t;
		t.loadFromFile("missile.png");
		temp->getDataSprite().at(0)->setTexture(t);
		//if (movement(lag, a, x, y))
			//temp->getDataSprite().at(0)->move(*x, *y);*/
		window->draw(*(temp->getDataSprite().at(0)));
	}
	if (a->hasComponent("Text"))
	{
		temp = a->getComponent("Text");
		if (movement(lag, a, x, y))
			temp->getDataText().at(0)->move(*x, *y);
		window->draw(*(temp->getDataText().at(0)));
	}
	if (a->hasComponent("CircleShape"))
	{
		temp = a->getComponent("CircleShape");
		if (movement(lag, a, x, y))
			temp->getDataCircleShape().at(0)->move(*x, *y);
		window->draw(*(temp->getDataCircleShape().at(0)));
	}
	if (a->hasComponent("ConvexShape"))
	{
		temp = a->getComponent("ConvexShape");
		if (movement(lag, a, x, y))
			temp->getDataConvexShape().at(0)->move(*x, *y);
		window->draw(*(temp->getDataConvexShape().at(0)));
	}
	if (a->hasComponent("RectangleShape"))
	{
		temp = a->getComponent("RectangleShape");
		if (movement(lag, a, x, y))
			temp->getDataRectangleShape().at(0)->move(*x, *y);
		window->draw(*(temp->getDataRectangleShape().at(0)));
	}

	window->display();
}


bool Render::movement(double lag, Entity* a, int* i, int* j)
{
	Property * temp2, *temp3;
	temp2 = nullptr;
	temp3 = nullptr;
	//Update position based on time lag.
	double x, y, changeX, changeY;
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
			x += changeX;
			y += changeY;
			//Store new position.
			*i = x;
			*j = y;

			return true;
		}
	}
	return false;
}
