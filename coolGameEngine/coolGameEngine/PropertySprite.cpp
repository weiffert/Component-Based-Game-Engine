#include "stdafx.h"
#include "PropertySprite.h"


PropertySprite::PropertySprite()
{
}


PropertySprite::~PropertySprite()
{
}


//Returns the data held in the vector.
std::vector<sf::Sprite> PropertySprite::getData()
{
	return data;
}


//Returns the data at the location.
sf::Sprite PropertySprite::getData(int location)
{
	if (location != data.size())
		return data.at(location);
	return NULL;
}


//Adds value to existing data
//Takes in data.
void PropertySprite::addData(sf::Sprite value)
{
	data.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertySprite::deleteData()
{
	for (int i = 0; i < data.size(); i++)
	{
		data.erase(data.begin() + i);
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertySprite::deleteData(sf::Sprite value)
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
void PropertySprite::deleteDataPosition(int position)
{
	if (position < data.size())
	{
		data.erase(data.begin() + position);
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
void PropertySprite::changeData(sf::Sprite value, int position)
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}

