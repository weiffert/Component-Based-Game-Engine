#include "StateLoading.h"


StateLoading::StateLoading(SystemManager *s)
{
	id = "Loading";
	number = 0;
	systemManager = s;
}


StateLoading::~StateLoading()
{
}


int StateLoading::update()
{
	//check if all of the entities have been initialized.
	//If not all of the entitites have been intitalized...
		//Do one.
	//If all of them have been, move on.
		//check which states have been initialized in SystemManager's vector of BaseState.
			//There are keywords for figuring out the state's class. Try typeof or typeid
		//If not all of the states have been initialized...
			//Initialize the state that is next in numeric order.
			//return 1;
		//Else...all of the states are made.
			//return -1;
}


void StateLoading::render(double lag)
{
	//Render the entities using the render controller.
	//Look something like render.control(*Entity, lag);
}
