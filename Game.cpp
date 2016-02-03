//includes
#include "Game.h"
#include <time.h>

Game::Game()
{

}

Game::~Game()
{

}


//Functions
int Game::run()
{
	//initialize managers
	//gameLoop
	//cleanup
	return exitCode;
}


int Game::gameLoop()
{
	bool running = true;

	//initialize time keepers
	double totaltime = 0.0;
	double frameRate = 0.01;

	double lag = 0.0;
	double currentTime = time(NULL);

	while(running)
	{
		//initialize current time keepers
		double newTime = time(NULL);
		double frameTime = newTime - currentTime;
		
		if (frameTime > 0.25)
			frameTime = 0.25;

		currentTime = newTime;

		lag += frameTime;
		//process input
		while (lag >= frameRate)
		{
			//update
			//decrement current time keepers
			totalTime += frameRate;
			lag -= frameRate;
		}
		//render with parameters.
		//render(lag/frameRate);
	}
	return exitCode;
}
