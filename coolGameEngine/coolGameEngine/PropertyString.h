#pragma once
#include "BaseComponent.h"

#include <string>

class PropertyString :
	public BaseComponent
{
public:
	PropertyString();
	~PropertyString();

	//Returns the data as a vector.
	std::vector<std::string> getData();
	std::string getData(int);

	//Edit the data.
	void addData(std::string);
	virtual void deleteData();
	void deleteData(std::string);
	virtual void deleteDataPosition(int);
	void changeData(std::string, int);

private:
	std::vector<float> data;
};

