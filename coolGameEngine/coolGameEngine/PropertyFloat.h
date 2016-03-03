#pragma once
#include "BaseComponent.h"
class PropertyFloat :
	public BaseComponent
{
public:
	PropertyFloat();
	~PropertyFloat();

	//Returns the data as a vector.
	std::vector<float> getData();
	float getData(int);

	//Edit the data.
	void addData(float);
	virtual void deleteData();
	void deleteData(float);
	virtual void deleteDataPosition(int);
	void changeData(float, int);

private:
	std::vector<float> data;
};

