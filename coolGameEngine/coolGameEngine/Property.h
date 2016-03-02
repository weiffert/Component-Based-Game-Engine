#pragma once
#include <vector>
#include "BaseComponent.h"

template <class T>
class Property : public BaseComponent
{
public:
	Property();
	~Property();

public:
	Property();
	~Property();

	//Returns the data as a vector.
	std::vector<T> getData();
	T getData(int);

	//Edit the data.
	void addData(T);
	void deleteData();
	void deleteData(T);
	void deleteDataPosition(int);
	void changeData(T, int);

private:
	std::vector<T> data;
};


//Default constructor
template <class T>
Property<T>::Property()
{

}


//Default destructor
template <class T>
Property<T>::~Property()
{

}


//Returns the data held in the vector.
template <class T>
std::vector<T> Property<T>::getData()
{
	return data;
}


//Returns the data at the location.
template <class T>
T Property<T>::getData(int location)
{
	if (location != data.size())
		return data.at(location);
	return NULL;
}


//Adds value to existing data
//Takes in data.
template <class T>
void Property<T>::addData(T value)
{
	data.push_back(value);
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
template <class T>
void Property<T>::deleteData()
{
	for (int i = 0; i < data.size(); i++)
	{
		data.erase(data.begin() + i);
	}
}


//Subtracts value from existing data.
//Takes in the data to be deleted.
template <class T>
void Property<T>::deleteData(T value)
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
template <class T>
void Property<T>::deleteDataPosition(int position)
{
	if (position < data.size())
	{
		data.erase(data.begin() + position);
	}
}


//Value changes the data at position.
//Takes in a value to change to and the position to change it at.
template <class T>
void Property<T>::changeData(T value, int position) 
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}
