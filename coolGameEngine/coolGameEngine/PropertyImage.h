#pragma once
#include "BaseComponent.h"

#include "SFML\Graphics.hpp"

class PropertyImage :
	public BaseComponent
{
public:
	PropertyImage();
	~PropertyImage();

	//Returns the data as a vector.
	std::vector<sf::Image> getData();
	sf::Image getData(int);

	//Edit the data.
	void addData(sf::Image);
	virtual void deleteData();
	void deleteData(sf::Image);
	virtual void deleteDataPosition(int);
	void changeData(sf::Image, int);

private:
	std::vector<sf::Image> data;
};

