/*
Authors: William Eiffert, Adam Sawyer, Zane Durante, Kendrick Austin
Date Begin: 3 February 2016
Last Edit: 19 February 2016
Purpose: This is a game engine designed to use entities and component based design.
The implementation of the engine will be missile command.
*/

//includes
#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <time.h>

int main()
{
	int exitCode = 0;
	
	//Log run
	std::filebuf fileControll;
	std::ostream file(&fileControll);
	fileControll.open("log.txt", std::ios::app);
	if (fileControll.is_open())
		file << "Program run at: " << time(NULL) << "\nExit Code: ";

	//Read from file.
	std::istream read(&fileControll);
	std::vector<std::string> data;
	int increment = 0;

	fileControll.open("game.txt", std::ios::app);
	if (fileControll.is_open())
	{
		while (!read.eof())
		{
			read >> data.at(increment);
			increment++;
		}
		fileControll.close();

		//Convert the first two strings to ints.
		int one = static_cast<int>(atoi(data.at(0).c_str())) - 48;
		int two = static_cast<int>(atoi(data.at(1).c_str())) - 48;

		//Create the game.
		int width;
		int height;
		std::string name;

		Game game(one, two, data.at(2));

		//run the game
		exitCode = game.run();

		//log exit code
		if (fileControll.is_open())
			file << exitCode;

	}

	else if (fileControll.is_open())
	{
		file << "404. Could not open game.txt";
	}


	//clean up
	fileControll.close();
	
	return 0;
}
