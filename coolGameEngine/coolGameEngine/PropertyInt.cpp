#include "stdafx.h"
#include "PropertyInt.h"


PropertyInt::PropertyInt()
{
}


PropertyInt::~PropertyInt()
{
}


//Returns the data held in the vector.
std::vector<int> PropertyInt::getData()
{
	return data;
}


//Returns the data at the location.
int PropertyInt::getData(int location)
{
	return data.at(location);
}


//Adds value to existing data
//Takes in data.
void PropertyInt::addData(int value)
{
	data.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyInt::deleteData()
{
	for (int i = 0; i < data.size(); i++)
	{
		data.erase(data.begin() + i);
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyInt::deleteData(int value)
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
void PropertyInt::deleteDataPosition(int position)
{
	if (position < data.size())
	{
		data.erase(data.begin() + position);
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
void PropertyInt::changeData(int value, int position)
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}
