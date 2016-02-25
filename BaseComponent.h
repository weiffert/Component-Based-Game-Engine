#pragma once

#include <string>


class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();

	//Edit id.
	std::string getId();
	void setId(std::string);

	//Returns the data as a vector.
	virtual std::vector<T> getData() = 0;
	virtual T getData(int) = 0;

	//Edit the data.
	virtual void addData(T) = 0;
	virtual void deleteData() = 0;
	virtual void deleteData(T) = 0;
	virtual void deleteDataPosition(int) = 0;
	virtual void changeData(T, int) = 0;

protected:
	std::string id;

	//contains the data in a vector style format.
	std::vector<T> data;
};

