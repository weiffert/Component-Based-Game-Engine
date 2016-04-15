#include "stdafx.h"

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Render.h"
#include "Property.h"
#include "Entity.h"
#include "AssetManager.h"

#include <iostream>

Render::Render()
{

}


Render::~Render()
{

}


//Draws an entity to a window. It can only do one part of the entity.
//Takes in the lag between updates, window, and the entity to be drawn.
void Render::control(double lag, sf::RenderWindow *window, Entity *a, AssetManager *assetManager)
{
	//Temp stores the property to be drawn.
	Property *temp;
	temp = nullptr;
	double x = 0, y = 0;

	//Check if it can be drawn.
	if (a->hasComponent("Draw"))
	{
		if (a->getComponent("Draw")->getDataBool().at(0) == true)
		{
			if (a->hasComponent("DrawSprite"))
			{
				if (a->getComponent("DrawSprite")->getDataBool().at(0) == true)
				{
					if (a->hasComponent("Sprite"))
					{
						temp = a->getComponent("Sprite");
						/*
						if (a->hasComponent("Move"))
						if (a->getComponent("Move")->getDataBool().at(0))
						if (movement(lag, a, x, y))
						temp->getDataSprite().at(0)->setPosition(x, y);*/
						for (int i = 0; i < temp->getDataSprite().size(); i++)
							window->draw(*(temp->getDataSprite().at(i)));
					}
				}
			}
			if (a->hasComponent("Text"))
			{
				temp = a->getComponent("Text");
				/*if (a->hasComponent("Move"))
					if (a->getComponent("Move")->getDataBool().at(0))
						if (movement(lag, a, x, y))
							temp->getDataText().at(0)->setPosition(x, y);*/
				for (int i = 0; i < temp->getDataText().size(); i++)
					window->draw(*(temp->getDataText().at(i)));
			}
			if (a->hasComponent("DrawCircleShape"))
			{
				if (a->getComponent("DrawCircleShape")->getDataBool().at(0) == true)
				{
					if (a->hasComponent("CircleShape"))
					{
						temp = a->getComponent("CircleShape");
						/*if (a->hasComponent("Move"))
						if (a->getComponent("Move")->getDataBool().at(0))
						if (movement(lag, a, x, y))
						temp->getDataCircleShape().at(0)->setPosition(x, y);*/
						for (int i = 0; i < temp->getDataCircleShape().size(); i++)
							window->draw(*(temp->getDataCircleShape().at(i)));
					}
				}
			}
			if (a->hasComponent("ConvexShape"))
			{
				temp = a->getComponent("ConvexShape");
				/*if (a->hasComponent("Move"))
					if (a->getComponent("Move")->getDataBool().at(0))
					if (movement(lag, a, x, y))
					temp->getDataConvexShape().at(0)->setPosition(x, y);*/
				for (int i = 0; i < temp->getDataConvexShape().size(); i++)
					window->draw(*(temp->getDataConvexShape().at(i)));
			}
			if (a->hasComponent("RectangleShape"))
			{
				if (a->hasComponent("DrawRectangleShape"))
				{
					if (a->getComponent("DrawRectangleShape")->getDataBool().at(0) == true)
					{
						if (a->hasComponent("DrawRectangleShape"))
						{
							temp = a->getComponent("RectangleShape");
							/*if (a->hasComponent("Move"))
								if (a->getComponent("Move")->getDataBool().at(0))
								if (movement(lag, a, x, y))
								temp->getDataRectangleShape().at(0)->setPosition(x, y);*/
							for (int i = 0; i < temp->getDataRectangleShape().size(); i++)
								window->draw(*(temp->getDataRectangleShape().at(i)));
						}
					}
				}
			}
		}
	}
}


bool Render::movement(double lag, Entity* a, double &i, double &j)
{
	Property * temp2, *temp3;
	temp2 = nullptr;
	temp3 = nullptr;
	//Update position based on time lag.
	double x, y, changeX, changeY;
	if (a->hasComponent("Velocity"))
	{
		//Holds the velocity.
		temp2 = a->getComponent("Velocity");

		if (a->hasComponent("CurrentPosition"))
		{
			//Holds the current position.
			temp3 = a->getComponent("CurrentPosition");

			//Update Position.
			//speed * lag = distance.
			x = temp3->getDataDouble().at(0);
			y = temp3->getDataDouble().at(1);
			changeX = temp2->getDataDouble().at(1) * lag;
			changeY = temp2->getDataDouble().at(2) * lag;
			x += changeX;
			y += changeY;
			//Store new position.
			i = x;
			j = y;

			return true;
		}
	}
	return false;
}
