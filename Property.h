#pragma once
#include <vector>

template <class T>
class Property
{
private:
	//contains the data in a vector style format.
	std::vector<T> data;

public:
	Property();
	Property(T);
	Property(T, T);
	~Property();
	std::vector<T> getData();
	void addData(T);
	void deleteData(T);
	void deleteDataPosition(int);
	void changeData(T, int);
};


//Default constructor
template <class T>
Property<T>::Property()
{

}


//Constructor and sets data to hold T
template <class T>
Property<T>::Property(T value)
{
	data.push_back(value);
}


//Constructor and sets data to hold T and T
template <class T>
Property<T>::Property(T value1, T value2)
{
	data.push_back(value1);
	data.push_back(value2);
}


//Default destructor
template <class T>
Property<T>::~Property()
{

}


//returns the data held in the vector.
//Needs to return data only if there is data.
template <class T>
std::vector<T> Property<T>::getData()
{
	if (data.at(0) != nullptr)
		return data;
	return nullptr;
}


template <class T>
void Property<T>::addData(T value)//adds value to existing data
{
	data.push_back(value);
}


template <class T>
void deleteData(T value)//subtracts value from existing data
{
	for (int i = 0; i < data.size(); i++)
	{
		if (data.at(i) == value)
		{
			data.erase(i);
		}
	}
}


void deleteDataPosition(int position)//subtracts value from existing data
{
	if (position < data.size())
	{
		data.erase(position);
	}
}


template <class T>
void changeData(T value, int position) //Value changes the data at position
{
	if (position < data.size())
		data.at(position) = value;
	else
		addData(value);
}
