#include "StateLoading.h"


StateLoading::StateLoading()
{
	id = "Loading";
	number = 1;
}


StateLoading::~StateLoading()
{
}


int StateLoading::update()
{
	//check which states have been initialized in SystemManager's vector of BaseState.
		//There are keywords for figuring out the state's class. Try typeof or typeid
	//Initialize the state that is next in numeric order.
}


void StateLoading::render(double lag)
{
	//Render the entities using the render controller.
	//Look something like render.control(*Entity, lag);
}
