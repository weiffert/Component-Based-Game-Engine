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
vector<T> Properties<T>::getData()//returns the data's value
{
	return data;
}

template <class T>
void Properties<T>::addData(T value)//adds to existing data
{
	data += value;
}

template <class T>
void deleteData(T value)//subtracts from existing data
{
	data -= value;
}

template <class T> 
void changeData(T value, int position) //Value canges the data, what is the need for int?
{
	data = value;
}