#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

#include "SystemManager.h"
#include "Entity.h"

class MissileExploder
{
public:
	MissileExploder();
	~MissileExploder();
	void control(SystemManager *, sf::RenderWindow *, Entity *);
};
