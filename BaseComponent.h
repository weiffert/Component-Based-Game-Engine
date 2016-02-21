#pragma once

#include <string>


class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();
	std::string getId();
	void setId(std::string);

protected:
	std::string id;
};

