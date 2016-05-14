#include "stdafx.h"
#include <string>
#include <vector>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "AssetManager.h"


AssetManager::AssetManager()
{

}


AssetManager::~AssetManager()
{
	//Delete all of the data in the vectors.
	/*
	while(!vector.empty())
	{
		delete vector.at(vector.size() - 1);
		vector.pop_back();
	}
	*/
}


//Takes in the location in the vector.
//Returns the type pointer for a property.
//type == data type.
//vector == a vector for each data type.
/*
type* AssetManager::getType(int location)
{
	if(location < vector.size() && location >= 0)
		return vector.at(location);
	return nullptr;
}
*/


//Takes in the filename.
//Returns the type pointer for a property.
//type == data type.
//vector == a vector for each data type.
//vectorNames == the corresponding type vector full of names for vector's data.
/*
type* AssetManager::getType(std::string filename)
{
	for(int i = 0; i < vectorNames.size(); i++)
	{
		if(vectorNames.at(i) == filename)
		{
			if(i < vector.size())
				return vector.at(i);
		}
	}
	return nullptr;
}
*/


//Adds an image to the vector for the state.
//Takes in a image.
/*
void AssetManager::add(type* a)
{
	vector.push_back(a);
}
*/


//Adds a name to be linked with the image.
//Takes in a string.
/*
void AssetManager::addTypeString(std::string a)
{
	vectorNames.push_back(a);
}
*/