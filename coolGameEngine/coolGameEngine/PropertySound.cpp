#include "stdafx.h"
#include "PropertySound.h"

#include "SFML\Audio.hpp"


PropertySound::PropertySound()
{
}


PropertySound::~PropertySound()
{
}


//Returns the data held in the vector.
std::vector<sf::Sound> PropertySound::getData()
{
	return data;
}


//Returns the data at the location.
sf::Sound PropertySound::getData(int location)
{
	return data.at(location);
}


//Adds value to existing data
//Takes in data.
void PropertySound::addData(sf::Sound value)
{
	data.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertySound::deleteData()
{
	for (int i = 0; i < data.size(); i++)
	{
		data.erase(data.begin() + i);
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertySound::deleteData(sf::Sound value)
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
void PropertySound::deleteDataPosition(int position)
{
	if (position < data.size())
	{
		data.erase(data.begin() + position);
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
void PropertySound::changeData(sf::Sound value, int position)
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}

