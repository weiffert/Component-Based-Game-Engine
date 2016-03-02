#pragma once
#include "BaseComponent.h"
class PropertyInt :
	public BaseComponent
{
public:
	PropertyInt();
	~PropertyInt();

	//Returns the data as a vector.
	std::vector<int> getData();
	int getData(int);

	//Edit the data.
	void addData(int);
	void deleteData();
	void deleteData(int);
	void deleteDataPosition(int);
	void changeData(int, int);

private:
	std::vector<int> data;
};

