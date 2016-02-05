#include "BaseController.h"


BaseController::BaseController()
{
	id = "BaseController"; //Autoset id to BaseController
}


BaseController::~BaseController()
{
}


//Returns id
std::string BaseController::getId()
{
	return id;
}


//Sets id
void BaseController::setId(std::string a)
{
	id = a;
	return;
}