#pragma once

#include <string>


class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();

	//Edit id.
	std::string getId();
	void setId(std::string);

protected:
	std::string id;
};

