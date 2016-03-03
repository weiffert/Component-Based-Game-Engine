#include "stdafx.h"
#include "PlayerInput.h"


PlayerInput::PlayerInput()
{
}


PlayerInput::~PlayerInput()
{
}

void contol(bool moveUp, bool moveDown, bool moveRight, bool moveLeft, bool spaceBarReleased, std::vector<sf::Entity> material)
{
	//Looks through all the entities until it finds the desired one
	//then saves the index of the desired entity so it can change its properties
	for (int x = 0; x++; x < material.size())
	{
		if (material.at(x)->getId() == "Player")
		{
			currentControl = x;
		}
	}
	if (material.at(x)->hasComponent("PlayerSprite") == true)
	{
		if (moveUp == true)
		{
			//The Default for movement is just up, down, left and right by default
			//When I get the actual sprite I will be moving I can make it rotate but I need to know where
			//I will set the origin on the sprite before I can do that
			material.at(x)->getComponent("PlayerSprite")->move(1, 0);
		}
		else if (moveDown == true)
		{
			material.at(x)->getComponent("PlayerSprite")->move(-1, 0);
		}
		if (moveRight == true)
		{
			material.at(x)->getComponent("PlayerSprite")->move(1, 0);
		}
		if (moveLeft == true)
		{
			material.at(x)->getComponent("PlayerSprite")->move(-1, 0);
		}
	}
}
