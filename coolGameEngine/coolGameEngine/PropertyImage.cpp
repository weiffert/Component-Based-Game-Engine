#include "stdafx.h"
#include "PropertyImage.h"

#include "SFML\Graphics.hpp"


PropertyImage::PropertyImage()
{
}


PropertyImage::~PropertyImage()
{
}


//Returns the data held in the vector.
std::vector<sf::Image> PropertyImage::getData()
{
	return data;
}


//Returns the data at the location.
sf::Image PropertyImage::getData(int location)
{
	return data.at(location);
}


//Adds value to existing data
//Takes in data.
void PropertyImage::addData(sf::Image value)
{
	data.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyImage::deleteData()
{
	for (int i = 0; i < data.size(); i++)
	{
		data.erase(data.begin() + i);
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyImage::deleteData(sf::Image value)
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
void PropertyImage::deleteDataPosition(int position)
{
	if (position < data.size())
	{
		data.erase(data.begin() + position);
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
void PropertyImage::changeData(sf::Image value, int position)
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}

