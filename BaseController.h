#pragma once
#include <string>
#include <vector>

#include "BaseComponent.h"


class BaseController
{
public:
	BaseController();
	~BaseController();
	std::string getId();
	void setId(std::string);
	void setRequiredProperties(vector<BaseComponent*> *);

protected:
	std::string id;
	std::vector<BaseComponent*> requiredProperty;
};

