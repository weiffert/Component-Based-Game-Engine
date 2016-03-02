#pragma once
#include "BaseComponent.h"

#include "Entity.h"

class PropertyEntity :
	public BaseComponent
{
public:
	PropertyEntity();
	~PropertyEntity();

	//Returns the data as a vector.
	std::vector<Entity> getData();
	Entity getData(int);

	//Edit the data.
	void addData(Entity);
	void deleteData();
	void deleteData(Entity);
	void deleteDataPosition(int);
	void changeData(Entity, int);

private:
	std::vector<Entity> data;
};

