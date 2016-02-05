#pragma once
template <class T>
class Properties
{
private:
	//contains the data in a vector style format.
	vector<T> data;

public:
	vector<T> getData();
	void addData(T);
	void deleteData(T);
	void changeData(T, int);

}

template <class T>
vector<T> Properties<T>::getData()//returns the data held in the vector
{
	return data.data();
}

template <class T>
void Properties<T>::addData(T value)//adds value to existing data
{
	data.push_back(value);
}

template <class T>
void deleteData(T value)//subtracts value from existing data
{
	for (int x = 0; x < data.size(); x++)
	{
		if (data.at(x) == value)
		{
			data.erase(x);
			break;
		}
	}
}

template <class T>
void changeData(T value, int position) //Value canges the data at position
{
	data.at(position) = value;
}
