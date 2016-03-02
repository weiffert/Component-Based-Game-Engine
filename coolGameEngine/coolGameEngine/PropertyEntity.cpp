#include "stdafx.h"
#include "PropertyEntity.h"

#include "Entity.h"


PropertyEntity::PropertyEntity()
{
}


PropertyEntity::~PropertyEntity()
{
}


//Returns the data held in the vector.
std::vector<Entity> PropertyEntity::getData()
{
	return data;
}


//Returns the data at the location.
Entity PropertyEntity::getData(int location)
{
	return data.at(location);
}


//Adds value to existing data
//Takes in data.
void PropertyEntity::addData(Entity value)
{
	data.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyEntity::deleteData()
{
	for (int i = 0; i < data.size(); i++)
	{
		data.erase(data.begin() + i);
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
void PropertyEntity::deleteData(Entity value)
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
void PropertyEntity::deleteDataPosition(int position)
{
	if (position < data.size())
	{
		data.erase(data.begin() + position);
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
void PropertyEntity::changeData(Entity value, int position)
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}

