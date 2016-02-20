#include "stdafx.h"
#include "BaseController.h"
#include "Entity.h"


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


void BaseController::setRequiredProperties(vector<std::BaseComponent*> *a)
{
	for (int i = 0; i < a->size(); i++)
		requiredProperty.push_back(a->at(i));
}