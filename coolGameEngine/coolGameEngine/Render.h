#pragma once
#include <vector>
#include <string>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "BaseController.h"
#include "AssetManager.h"
#include "Entity.h"
#include "Property.h"

class Render :
	public BaseController
{
public:
	Render();
	~Render();

	//Control function
	void control(double, sf::RenderWindow *, Entity *, AssetManager *);

private:
	bool movement(double, Entity*, double&, double&);
};

