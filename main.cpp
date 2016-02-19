/*
Authors: William Eiffert, Adam Sawyer, Zane Durante, Kendrick Austin
Date Begin: 3 February 2016
Last Edit: 18 February 2016
Purpose: This is a game engine designed to use entities and component based design.
The implementation of the engine will be missile command.
*/

//includes
#include "Game.h"
#include <fstream>
#include <time.h>

int main()
{
	int exitCode = 0;
	
	//Log run
	ostream file;
	file.open("log.txt"; ios::app);
	if (file.is_open())
		file << "Program run at: " << time(NULL); 

	//Create the game.
	Game game;

	//run the game
	exitCode = game.run();

	//log exit code
	if (file.is_open())
		file << "\nExit Code: " << exitCode << endl;

	//clean up
	file.close();
	
	return 0;
}
