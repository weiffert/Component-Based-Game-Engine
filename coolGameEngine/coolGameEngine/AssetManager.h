#pragma once
#include <string>
#include <vector>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

class BaseState;

class AssetManager
{
public:
	AssetManager();

	//Destructor. Deletes the data from the vectors.
	~AssetManager(); 

	//Return the proper data.
	//type* getType(int);
	//type* getType(std::string);

	//Adds the proper data.
	//void add(type*);
	//void addTypeString(std::string);

private:
	//Holds the data.
	//std::vector<type*> type;

	//Holds strings in the same position as the data.
	//std::vector<std::string> typeNames;
};
