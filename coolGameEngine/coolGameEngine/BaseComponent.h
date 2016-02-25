#pragma once

#include <string>
#include <vector>



class BaseComponent 
{
public:
	BaseComponent();
	~BaseComponent();

	//Edit id.
	std::string getId();
	void setId(std::string);

	//Returns the data as a vector.
	template <class T>
	virtual std::vector<T> getData() = 0;

	template <class T>
	virtual T getData(int) = 0;

	//Edit the data.
	template <class T>
	virtual void addData(T) = 0;

	virtual void deleteData() = 0;

	template <class T>
	virtual void deleteData(T) = 0;

	virtual void deleteDataPosition(int) = 0;

	template <class T>
	virtual void changeData(T, int) = 0;

protected:
	std::string id;

	//contains the data in a vector style format.
	//std::vector<T> data;
};

