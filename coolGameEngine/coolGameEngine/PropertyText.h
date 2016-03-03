#pragma once
#include "BaseComponent.h"

#include "SFML\Graphics.hpp"

class PropertyText :
	public BaseComponent
{
public:
	PropertyText();
	~PropertyText();

	//Returns the data as a vector.
	std::vector<sf::Text> getData();
	sf::Text getData(int);

	//Edit the data.
	void addData(sf::Text);
	virtual void deleteData();
	void deleteData(sf::Text);
	virtual void deleteDataPosition(int);
	void changeData(sf::Text, int);

private:
	std::vector<sf::Text> data;
};

