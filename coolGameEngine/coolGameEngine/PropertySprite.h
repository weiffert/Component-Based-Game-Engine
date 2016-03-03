#pragma once
#include "BaseComponent.h"

#include "SFML\Graphics.hpp"

class PropertySprite :
	public BaseComponent
{
public:
	PropertySprite();
	~PropertySprite();

	//Returns the data as a vector.
	std::vector<sf::Sprite> getData();
	sf::Sprite getData(int);

	//Edit the data.
	void addData(sf::Sprite);
	virtual void deleteData();
	void deleteData(sf::Sprite);
	virtual void deleteDataPosition(int);
	void changeData(sf::Sprite, int);

private:
	std::vector<sf::Sprite> data;
};

