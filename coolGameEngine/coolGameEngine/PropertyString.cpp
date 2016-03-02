#include "stdafx.h"
#include "PropertyString.h"

#include <string>


PropertyString::PropertyString()
{
}


PropertyString::~PropertyString()
{
}


//Returns the data held in the vector.
std::vector<std::string> PropertyString::getData()
{
	return data;
}


//Returns the data at the location.
std::string PropertyString::getData(int location)
{
	return data.at(location);
}


//Adds value to existing data
//Takes in data.
void PropertyString::addData(std::string value)
{
	data.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyString::deleteData()
{
	for (int i = 0; i < data.size(); i++)
	{
		data.erase(data.begin() + i);
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyString::deleteData(std::string value)
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
void PropertyString::deleteDataPosition(int position)
{
	if (position < data.size())
	{
		data.erase(data.begin() + position);
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
void PropertyString::changeData(std::string value, int position)
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}
