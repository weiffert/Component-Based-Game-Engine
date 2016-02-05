#pragma once
#include <string>
class StateLoading 
{
private:
	const int number = 1;
	const std::string id = "StateLoading";

public:
	void render();
	void update();
	const int getNumber();
	const std::string getId();
};