#pragma once
#include "BaseComponent.h"
class PropertyChar :
	public BaseComponent
{
public:
	PropertyChar();
	~PropertyChar();

	//Returns the data as a vector.
	std::vector<char> getData();
	char getData(int);

	//Edit the data.
	void addData(char);
	virtual void deleteData();
	void deleteData(char);
	virtual void deleteDataPosition(int);
	void changeData(char, int);

private:
	std::vector<char> data;
};

