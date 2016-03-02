#include "stdafx.h"
#include "PropertyChar.h"


PropertyChar::PropertyChar()
{
}


PropertyChar::~PropertyChar()
{
}


//Returns the data held in the vector.
std::vector<char> PropertyChar::getData()
{
	return data;
}


//Returns the data at the location.
char PropertyChar::getData(int location)
{
	return data.at(location);
}


//Adds value to existing data
//Takes in data.
void PropertyChar::addData(char value)
{
	data.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyChar::deleteData()
{
	for (int i = 0; i < data.size(); i++)
	{
		data.erase(data.begin() + i);
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyChar::deleteData(char value)
{
	for (int i = 0; i < data.size(); i++)
	{
		if (data.at(i) == value)
		{
			data.erase(data.begin() + i);
		}
	}
}


//Subtracts value from existing data with the position.
//Takes in the position with data to be deleted.
void PropertyChar::deleteDataPosition(int position)
{
	if (position < data.size())
	{
		data.erase(data.begin() + position);
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
void PropertyChar::changeData(char value, int position)
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}

