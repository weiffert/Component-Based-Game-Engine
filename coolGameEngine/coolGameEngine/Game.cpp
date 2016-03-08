#include "stdafx.h"

#include <string>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "Game.h"
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "StateLoading.h"


//Constructor. Takes in the window width, height, and name.
Game::Game(int width, int height, std::string name)
{
	sf::VideoMode windowResolution;
	windowResolution.width = width;
	windowResolution.height = height;
	gameName = name;
	systemManager = new SystemManager();
	assetManager = new AssetManager();
}


Game::~Game()
{

}


//Runs the game.
//Returns the exit code.
int Game::run()
{
	//Create a state loading to start the game with.
	state = new StateLoading (systemManager, assetManager);
	//Add it to the systemManager.
	systemManager->add(state);
	//run the game loop, which returns the exit code.
	exitCode = gameLoop();

	return exitCode;
}


//Runs the game loop.
//Returns the exit code.
int Game::gameLoop()
{
	//initialize time keepers
	double totalTime = 0.0;
	double frameRate = 0.01;

	double lag = 0.0;
	double currentTime = time(NULL);

	//Run while the game window is open.
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
			state->update(totalTime, &gameWindow);
			//decrement current time keepers
			totalTime += frameRate;
			lag -= frameRate;
		}
		//render with parameters.
		state->render(lag/frameRate, &gameWindow);
	}

	return exitCode;
}
