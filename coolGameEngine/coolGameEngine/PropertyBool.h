#pragma once
#include "BaseComponent.h"
class PropertyBool :
	public BaseComponent
{
public:
	PropertyBool();
	~PropertyBool();

	//Returns the data as a vector.
	std::vector<bool> getData();
	bool getData(int);

	//Edit the data.
	void addData(bool);
	virtual void deleteData();
	void deleteData(bool);
	virtual void deleteDataPosition(int);
	void changeData(bool, int);

private:
	std::vector<bool> data;
};

