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

	int control();

private:
	std::string id;
	std::vector<BaseComponent*> requiredProperty;
};

