#include "stdafx.h"

#include <string>;
#include <vector>;

#include "BaseController.h"
#include "BaseComponent.h"


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


void BaseController::setRequiredProperties(std::vector<std::BaseComponent*> *a)
{
	for (int i = 0; i < a->size(); i++)
		requiredProperty.push_back(a->at(i));
}