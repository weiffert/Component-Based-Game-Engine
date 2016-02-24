#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "BaseState.h"
#include "StateLoading.h"
#include "StateWelcome.h"
#include "StateEnd.h"
#include "StateMenu.h"
#include "StatePause.h"
#include "StateLevel.h"
#include "Property.h"
#include "Entity.h"
#include "BaseController.h"
#include "SystemManager.h"
#include "AssetManager.h"


StateLoading::StateLoading(SystemManager *s, AssetManager *a)
{
	id = "Loading";
	number = 0;
	systemManager = s;
	assetManager = a;

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
	substringSorter();
}


StateLoading::~StateLoading()
{
}


std::string StateLoading::fileDeterminer()
{
	for (int i = 0; i < filenames.size(); i++)
	{
		if (filenames.at(i).find(substrings.at(0)) != std::string::npos)
		{
			std::string temp = filenames.at(i);
			filenames.erase(i);
			return temp;
		}
	}

	substrings.erase(0);
	return nullptr;
}


//Sorts the substrings into a particular order.
void StateLoading::substringSorter()
{
	for (int i = 0; i < substrings.size(); i++)
	{
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

		if (substrings.at(1) != sub)
		{
			for (int j = i; j < substrings.size(); i++)
			{
				if (substrings.at(j) == sub)
				{
					std::string temp = substrings.at(j);
					substrings.at(j) = substrings.at(i);
					substrings.at(i) = temp;
				}
			}
		}
	}
}


void StateLoading::update(double totalTime, sf::RenderWindow *window)
{
	if (substrings.size() != 0)
	{
		std::string id;
		std::string filename;
		std::string word;
		int lineNumber = 1; //The line number of the file
		int wordNumber = 1; //Determines which word of the line (1st, 2nd, 3rd, words in a line or more)
		//Determine the file to parse data from.
		filename = fileDeterminer();
		std::ifstream file (filename);
		std::string type;

		//Determine the operation.
		if (substrings.at(0) == "png")
		{
			sf::Image *temp;
			temp->loadFromFile(filename);
			assetManager->add(temp);
		}

		else if (substrings.at(0) == "property")
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

			//Create.
			BaseComponent *temp;
		
			if (type == "int")
			{
				temp = new Property<int>();
				std::vector<int> vectorInt;
					for (int i = 0; i < data.size(); i++)
					{
						vectorInt.push_back(std::stoi(data.at(i)));
						temp->addData(vectorInt.at(i));
					}
				
			}
				
			else if (type == "char")
				temp = new Property<char>();

			else if (type == "double")
				temp = new Property<double>();

			else if (type == "float")
				temp = new Property<float>();

			else if (type == "bool")
				temp = new Property<bool>();

			else if (type == "string")
				temp = new Property<std::string>();

			else if (type == "Entity")
				temp = new Property<Entity>();	//Does this work?
								//temp->getComponent(id) store this as data

			else if (type == "Texture")
				temp = new Property<sf::Texture>();

			else if (type == "Image")
				temp = new Property<sf::Image>();

			else if (type == "Sound")
				temp = new Property<sf::Sound>();

			else
				temp = new Property<std::string>();


			//Edit.
			temp->setId(id);
			//Adding data.
			for (int i = 0; i < data.size(); i++)
				temp->addData(data.at(i));

			//Store.
			systemManager->add(temp);

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
			Entity *temp = new Entity();

			//Edit.
			temp->setId(id);
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
							temp->add(component);
						}
						//Change Data.
						else
						{
							//Needs to be converted to the proper type.
							if (type == "int")
								temp->getComponent(properties.at(y).at(0))->changeData
								(static_cast<int>(properties.at(y).at(x)) - 48, x - 1);

							else if (type == "char")
								temp->getComponent(properties.at(y).at(0))->changeData
								(properties.at(y).at(x).at(1), x - 1);

							else if (type == "double")
								temp->getComponent(properties.at(y).at(0))->changeData
								(static_cast<double>(properties.at(y).at(x)) - 48, x - 1);

							else if (type == "float")
								temp->getComponent(properties.at(y).at(0))->changeData
								(static_cast<float>(properties.at(y).at(x)) - 48, x - 1);
			
							else if (type == "bool")
								{
									bool tOrF = false;
									if (properties.at(y).at(x) == "true")
										tOrF = true;
									temp->getComponent(properties.at(y).at(0))->changeData
									(tOrF, x - 1);
								}
		
							else if (type == "string")
								temp->getComponent(properties.at(y).at(0))->changeData
								(properties.at(y).at(x), x - 1);
				
							else if (type == "Entity")
								temp->getComponent(properties.at(y).at(0))->changeData
								(systemManager->getMaterial(properties.at(y).at(x)), x - 1);
				
							else if (type == "Texture")
								temp->getComponent(properties.at(y).at(0))->changeData
								(assetManager->getTexture(properties.at(y).at(x)), x - 1);
				
							else if (type == "Image")
								temp->getComponent(properties.at(y).at(0))->changeData
								(assetManager->getComponent(properties.at(y).at(x)), x - 1);
				
							else if (type == "Sound")
								temp->getComponent(properties.at(y).at(0))->changeData
								(assetManager->getSound(properties.at(y).at(x)), x - 1);
				
							else
								temp->getComponent(properties.at(y).at(0))->changeData
								(properties.at(y).at(x), x - 1);
						}
					}
					//Link the property.
					else
						temp->add(systemManager->getComponent(properties.at(y).at(x)));
				}
			}

			//Store.
			systemManager->add(temp);

		}
		else if (substrings.at(0) == "controller")
		{
			std::vector<std::string> properties;
			//Get id and required properties.
			while (!file.eof())
			{
				file >> word;
				while (word != ";") //Read until the end of the line
				{
					if (lineNumber == 1)
						id = word;
					if (lineNumber > 2)
						properties.push_back(word);
					file >> word;
				}
				//Increase line number
				lineNumber++;
			}
			
			BaseController *temp = new /*Id*/();

			vector<BaseComponent> components;
			for (int i = 0; i < properties.size(); i++)
				components.push_back(systemManager->getProperty(properties.at(i));

		}
		else if (substrings.at(0) == "state")
		{
			std::string number;
			int intNumber;
			BaseState *temp;

			//read data and take in values. Includes id.
			while (!file.eof())
			{
				file >> word;
				while (word != ";") //Read until the end of the line
				{
					if (lineNumber == 1)
						id = word;
					if (lineNumber > 2)
							number = word;
					file >> word;
				}
				//Increase line number
				lineNumber++;
			}

			//Determine the state.
			intNumber = static_cast<int>(atoi(number.c_str))-48;

			//Create
			switch (intNumber)
			{
			case 1:
				temp = new StateLoading(systemManager, assetManager);
				break;
			case 2:
				temp = new StateWelcome(systemManager, assetManager);
				break;
			case 3:
				temp = new StateMenu(systemManager, assetManager);
				break;
			case 4:
				temp = new StateLevel(systemManager, assetManager);
				break;
			case 5:
				temp = new StateEnd(systemManager, assetManager);
				break;
			case 6:
				temp = new StatePause(systemManager, assetManager);
				break;
			}

			//Edit
			temp->setId(id);
			temp->setNumber(intNumber);
			temp->setMaterial(systemManager->getMaterial(temp));

			//Store
			systemManager->add(temp);
		}
	}

	//the process is done.
	else
	{
		//change state.
	}
}
