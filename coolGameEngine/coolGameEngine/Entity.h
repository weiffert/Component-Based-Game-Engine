#pragma once
#include <string>
#include <vector>

/*
#include "Property.h"
#include "BaseController.h"
*/

class Property;
class BaseController;

class Entity
{
public:
	Entity();
	~Entity();

	//Change the id.
	std::string getId();
	void setId(std::string);

	//Add classes to the proper vector.
	void add(Property*);

	//Remove the proper class from the proper vector.
	void remove(Property*);
	void deleteComponent(std::string);

	//Returns a boolean value if the proper vector contains a the correct class.
	bool hasComponent(std::string);

	//Returns the correct class if there is one with the correct id.
	Property* getComponent(std::string);

private:
	std::string id;
	std::vector<Property *> component;
};
