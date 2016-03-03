#pragma once
#include "BaseComponent.h"

#include "SFML\Graphics.hpp"

class PropertyShape :
	public BaseComponent
{
public:
	PropertyShape();
	~PropertyShape();

	//Returns the data as a vector.
	std::vector<sf::Shape> getData();
	sf::Shape getData(int);

	//Edit the data.
	void addData(sf::Shape);
	virtual void deleteData();
	void deleteData(sf::Shape);
	virtual void deleteDataPosition(int);
	void changeData(sf::Shape, int);

private:
	std::vector<sf::Shape> data;
};

