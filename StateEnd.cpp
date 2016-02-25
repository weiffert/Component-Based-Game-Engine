#include "stdafx.h"

#include <vector>
#include <fstream>
#include <string>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "StateEnd.h"
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "StateLoading.h"
#include "Entity.h"



//SFML includes

StateEnd::StateEnd(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "End";
	number = 4;
	systemManager = s;
	assetManager = a;

	//Reads in the filenames and substrings.
	std::ifstream file("file.txt");
	if (file.is_open())
	{
		std::string temp;
		while (!file.eof())
		{
			if (temp == "Filenames")
			{
				while (temp != "Substrings" && !file.eof())
				{
					file >> temp;
					filenames.push_back(temp);
				}
			}
			if (temp == "Substrings")
			{
				while (temp != "Filenames" && !file.eof())
				{
					file >> temp;
					filenames.push_back(temp);
				}
			}
		}
	}

	//Sorts the substrings into the proper order.
	substringSorter();
}


StateEnd::~StateEnd()
{
}


//Determines the proper file to use based off of the current substring.
//Deletes the filename once it has been determined. Deletes the substring after all of its files have been used.
std::string StateLoading::fileDeterminer()
{
	//Passes through all of the filenames.
	for (int i = 0; i < filenames.size(); i++)
	{
		//If the base substring is found in the filename...
		if (filenames.at(i).find(substrings.at(0)) != std::string::npos)
		{
			std::string temp = filenames.at(i);
			filenames.erase(i);
			return temp;
		}
	}

	//There are no filenames with this substring name, so it is done.
	substrings.erase(0);
	return nullptr;
}


//Sorts the substrings into a particular order.
void StateLoading::substringSorter()
{
	//Passes through all of the substrings.
	for (int i = 0; i < substrings.size(); i++)
	{
		//Stores the substring that is supposed to be at that position.
		std::string sub;
		switch (i)
		{
		case 0:
			sub = "png";
			break;
		case 1:
			sub = "property";
			break;
		case 2:
			sub = "entity";
			break;
		case 3:
			sub = "controller";
			break;
		case 4:
			sub = "state";
			break;
		default:
			sub = "default";
		}

		//If it is not in the proper position...
		if (substrings.at(1) != sub)
		{
			//Pass through all of the rest of the substrings.
			for (int j = i; j < substrings.size(); i++)
			{
				//If one does equal the proper substring...
				if (substrings.at(j) == sub)
				{
					//Switch positions.
					std::string temp = substrings.at(j);
					substrings.at(j) = substrings.at(i);
					substrings.at(i) = temp;
				}
			}
		}
	}
}


void StateEnd::update(double totalTime, sf::RenderWindow* window)
{
	if (substrings.size() != 0)
	{
		std::string id = " ";
		std::string filename;
		std::string word;
		int lineNumber = 1; //The line number of the file
		int wordNumber = 1; //Determines which word of the line (1st, 2nd, 3rd, words in a line or more)
		//Determine the file to parse data from.
		filename = fileDeterminer();
		std::ifstream file(filename);
		std::string type;

		//Determine the operation.
		if (substrings.at(0) == "property")
		{
			std::vector<std::string> data;
			

			//Read data and take in these values. Includes id

			//Read entire file
			while (!file.eof())
			{
				file >> word;
				while (word != ";") //Read until the end of the line
				{
					if (lineNumber == 1)
						id = word;
					if (lineNumber == 2)
						type = word;
					if (lineNumber > 2)
						data.push_back(word);
					file >> word;
				}
				//Increase line number
				lineNumber++;
			}
			BaseComponent *temp = systemManager->getComponent(id);

			if (temp != nullptr)
			{
				//Adding data.
				for (int i = 0; i < data.size(); i++)
					temp->changeData(data.at(i));
			}

		}
		else if (substrings.at(0) == "entity")
		{
			std::vector<std::vector<std::string>>properties;   //The first vector is for holding all properties. The second is for holding id 
			//and data of the properties.

			//Read data and take in these values. Includes id.
			while (!file.eof())
			{
				file >> word;
				while (word != ";") //Read until the end of the line
				{
					if (lineNumber == 1)
						id = word;
					if (lineNumber > 1)
					{
						if (wordNumber == 1)
							properties.at(lineNumber - 1).at(wordNumber - 1);
					}

					file >> word;
					wordNumber++;
				}
				lineNumber++;	//Increase line number
				wordNumber = 1; //Set wordNumber back to 1
			}

			//Create.
			Entity *temp = systemManager->getMaterial(id);

			//Edit.
			//Loop for the vector.
			for (int y = 0; y < properties.size(); y++)
			{
				//Loop for the vector in the vector.
				for (int x = 0; x < properties.at(y).size(); x++)
				{
					//If there is data.
					if (properties.at(y).size() > 1)
					{
						//If it is the first iteration, clone the property.
						if (x == 0)
						{
							BaseComponent *component = systemManager->getComponent(properties.at(y).at(x));
							systemManager->add(component);
							temp->remove(component);
							temp->add(component);
						}
						//Change Data.
						else
						{
							//Needs to be converted to the proper type.
							if (type == "int")
								temp->getComponent(properties.at(y).at(0))->changeData(static_cast<int>(properties.at(y).at(x)) - 48, x - 1);
							else if (type == "char")
								temp->getComponent(properties.at(y).at(0))->changeData(properties.at(y).at(x).at(1), x - 1);
							else if (type == "double")
								temp->getComponent(properties.at(y).at(0))->changeData(static_cast<double>(properties.at(y).at(x)) - 48, x - 1);
							else if (type == "float")
								temp->getComponent(properties.at(y).at(0))->changeData(static_cast<float>(properties.at(y).at(x)) - 48, x - 1);
							else if (type == "bool")
							{
								bool tOrF = false;
								if (properties.at(y).at(x) == "true")
									tOrF = true;
								temp->getComponent(properties.at(y).at(0))->changeData(tOrF, x - 1);
							}
							else if (type == "string")
								temp->getComponent(properties.at(y).at(0))->changeData(properties.at(y).at(x), x - 1);
							else if (type == "Entity")
								temp->getComponent(properties.at(y).at(0))->changeData(systemManager->getMaterial(properties.at(y).at(x)), x - 1);
							else if (type == "Texture")
								temp->getComponent(properties.at(y).at(0))->changeData(assetManager->getTexture(properties.at(y).at(x)), x - 1);
							else if (type == "Image")
								temp->getComponent(properties.at(y).at(0))->changeData(assetManager->getComponent(properties.at(y).at(x)), x - 1);
							else if (type == "Sound")
								temp->getComponent(properties.at(y).at(0))->changeData(assetManager->getSound(properties.at(y).at(x)), x - 1);
							else
								temp->getComponent(properties.at(y).at(0))->changeData(properties.at(y).at(x), x - 1);

						}
					}
					else //Link the property.
						temp->add(systemManager->getComponent(properties.at(y).at(x)));
				}
			}
		}
	}
}
