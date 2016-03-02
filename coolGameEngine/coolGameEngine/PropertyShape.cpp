#include "stdafx.h"
#include "PropertyShape.h"

#include "SFML\Graphics.hpp"


PropertyShape::PropertyShape()
{
}


PropertyShape::~PropertyShape()
{
}


//Returns the data held in the vector.
std::vector<sf::Shape> PropertyShape::getData()
{
	return data;
}


//Returns the data at the location.
sf::Shape PropertyShape::getData(int location)
{
	return data.at(location);
}


//Adds value to existing data
//Takes in data.
void PropertyShape::addData(sf::Shape value)
{
	data.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyShape::deleteData()
{
	for (int i = 0; i < data.size(); i++)
	{
		data.erase(data.begin() + i);
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyShape::deleteData(sf::Shape value)
{
	for (int i = 0; i < data.size(); i++)
	{
		if (&data.at(i) == &value)
		{
			data.erase(data.begin() + i);
		}
	}
}


//Subtracts value from existing data with the position.
//Takes in the position with data to be deleted.
void PropertyShape::deleteDataPosition(int position)
{
	if (position < data.size())
	{
		data.erase(data.begin() + position);
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
void PropertyShape::changeData(sf::Shape value, int position)
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}

