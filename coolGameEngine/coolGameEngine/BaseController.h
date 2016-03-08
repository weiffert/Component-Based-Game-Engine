#pragma once
#include <string>
#include <vector>

/*
#include "Property.h"
*/

class Property;

class BaseController
{
public:
	BaseController();
	~BaseController();

	//Change Id.
	std::string getId();
	void setId(std::string);

	//Set required properties.
	void setRequiredProperties(std::vector<Property*> *);

protected:
	std::string id;
	std::vector<Property*> requiredProperty;
};

