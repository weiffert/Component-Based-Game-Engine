#pragma once

#include <string>
using std::string;

class BaseComponent
{
public:
	BaseComponent();
	~BaseComponent();
	string getId();
	void setId(string);
private:
	string id;
};

