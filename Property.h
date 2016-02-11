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


template <class T>
std::vector<T> Property<T>::getData()//returns the data held in the vector
{
	return data.data();
}


template <class T>
void Property<T>::addData(T value)//adds value to existing data
{
	data.push_back(value);
}


//Currently deletes all data with the same value.
template <class T>
void deleteData(T value)//subtracts value from existing data
{
	for (int x = 0; x < data.size(); x++)
	{
		if (data.at(x) == value)
		{
			data.erase(x);
		}
	}
}


template <class T>
void changeData(T value, int position) //Value changes the data at position
{
	data.at(position) = value;
}
