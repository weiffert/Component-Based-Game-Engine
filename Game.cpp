#include "stdafx.h"
#include "Game.h"
#include "SystemManager.h"
#include "StateLoading.h"
#include <time.h>
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

Game::Game(int width, int height, std::string name)
{
	windowResolution.x = width;
	windowResolution.y = height;
	gameName = name;
}

Game::~Game()
{

}


//Functions
int Game::run()
{
	//Enter Desired Game name and resolution into the render window functions
	//Considering reading window name and resolution from a file.
	

	state = new StateLoading* (systemManager);
	systemManager->addState(state);
	exitCode = gameLoop();
	//cleanup
	return exitCode;
}


int Game::gameLoop()
{
	bool running = true;
	int changeStateFlag = 1;
	//initialize time keepers
	double totalTime = 0.0;
	double frameRate = 0.01;

	double lag = 0.0;
	double currentTime = time(NULL);

	while(gameWindow.isOpen())
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
			changeStateFlag = state->update(totalTime);
			//decrement current time keepers
			totalTime += frameRate;
			lag -= frameRate;
		}
		//render with parameters.
		state->render(lag/frameRate, &gameWindow);
		
		/*


		Moved into the update functions.
		enum changeState { quit = -1, stay = 0, change = 1, weird = 2};
		switch(changeStateFlag)
		{
		case change:
			switch (state->getNumber())
			{
			case 6:
				stateLast = state;
				changeState(state, stateLast->getNumber());
				break;

			default:
				stateLast = state;
				changeState(state);
			}
			break;

		//Covers the second choice in StatePause.
		case weird:
			stateLast = state;
			changeState(state, 3);
			break;

		case quit:
			window.close();
		}
		*/
	}
	return exitCode;
}


//Be put in a controller.
//Exceptions are thrown in the getState.
void Game::changeState(BaseState *a)
{
	int tempInt = a->getNumber();
	a = systemManager->getState(tempInt+1);
}


//Exceptions are thrown in the getState.
void Game::changeState(BaseState *a, std::string s)
{
	a = systemManager->getState(s);
}


//Exceptions are thrown in the getState.
void Game::changeState(BaseState *a, int i)
{
	a = systemManager->getState(i);
}
