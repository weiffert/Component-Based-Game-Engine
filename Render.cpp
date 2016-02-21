#include "stdafx.h"

#include "Render.h"

Render::Render()
{

}


Render::~Render()
{

}


void Render::control(sf::RenderWindow *window, Entity *a)
{
	bool drawable = false;
	BaseComponent *temp;
	if (a->hasComponent("draw"))
	{
		if (a->hasComponent("Sprite"))
		{
			if (a->hasComponent("Image"))
			{
				drawable = true;
				temp = a->getComponent("Image");
			}
			if (a->hasComponent("Texture"))
			{
				drawable = true;
				temp = a->getComponent("Texture");
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
		if (drawable)
		{
			window.draw(temp);
		}
	}
}