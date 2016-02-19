/*
Authors: William Eiffert, Adam Sawyer, Zane Durante, Kendrick Austin
Date Begin: 3 February 2016
Last Edit: 19 February 2016
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
		file << "Program run at: " << time(NULL) << "\nExit Code: ";

	//Read from file.
	istream read;
	vector<std::string> data;
	int increment = 0;

	read.open("game.txt");
	if (read.is_open())
	{
		while (!read.eof())
		{
			read >> data.at(increment);
			increment++;
		}
		read.close();

		//Convert the first two strings to ints.
		int one = static_cast<int>(data.at(0)) - 48;
		int two = static_cast<int>(data.at(1)) - 48;

		//Create the game.
		Game game();

		//run the game
		exitCode = game.run(one, two, data.at(2));

		//log exit code
		if (file.is_open())
			file << exitCode << endl;

	}

	else if (file.is_open())
	{
		file << "404. Could not open game.txt" << endl;
	}


	//clean up
	file.close();
	
	return 0;
}
