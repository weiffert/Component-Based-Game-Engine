#pragma once
#include <vector>
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
class PlayerInput
{
public:
	PlayerInput();
	//Control function here that takes in a bool for each key that the player presses and reacts by 
	//performing actions such as moving or shooting.
	void control(bool, bool, bool, bool, bool, std::vector<sf::Entity>);
	~PlayerInput();
};

