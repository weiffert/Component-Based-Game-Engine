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
//						if (a->hasComponent("Move"))
//							if (a->getComponent("Move")->getDataBool().at(0))
//								if (movement(lag, a, x, y))
//									temp->getDataSprite().at(0)->setPosition(x, y);
						window->draw(*(temp->getDataSprite().at(0)));
					}
				}
			}
			if (a->hasComponent("Text"))
			{
				temp = a->getComponent("Text");
				if (a->hasComponent("Move"))
					if (a->getComponent("Move")->getDataBool().at(0))
						if (movement(lag, a, x, y))
							temp->getDataText().at(0)->setPosition(x, y);
				window->draw(*(temp->getDataText().at(0)));
			}
			if (a->hasComponent("CircleShape"))
			{
				temp = a->getComponent("CircleShape");
				if (a->hasComponent("Move"))
					if (a->getComponent("Move")->getDataBool().at(0))
						if (movement(lag, a, x, y))
							temp->getDataCircleShape().at(0)->setPosition(x, y);
				window->draw(*(temp->getDataCircleShape().at(0)));
			}
			if (a->hasComponent("ConvexShape"))
			{
				temp = a->getComponent("ConvexShape");
				if (a->hasComponent("Move"))
					if (a->getComponent("Move")->getDataBool().at(0))
						if (movement(lag, a, x, y))
							temp->getDataConvexShape().at(0)->setPosition(x, y);
				window->draw(*(temp->getDataConvexShape().at(0)));
			}
			if (a->hasComponent("RectangleShape"))
			{
				temp = a->getComponent("RectangleShape");
				if (a->hasComponent("Move"))
					if (a->getComponent("Move")->getDataBool().at(0))
						if (movement(lag, a, x, y))
							temp->getDataRectangleShape().at(0)->setPosition(x, y);
				window->draw(*(temp->getDataRectangleShape().at(0)));
			}
			/*
			if (a->hasComponent("ChemTrail"))
			{
			temp = a->getComponent("ChemTrail");
			sf::VertexArray lines(sf::LinesStrip, 2);
			lines[0].position = sf::Vector2f(temp->getDataLine().at(0), temp->getDataLine().at(1));
			lines[1].position = sf::Vector2f(temp->getDataLine().at(2), temp->getDataLine().at(3));

			window->draw(lines);
			}
			*/
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
