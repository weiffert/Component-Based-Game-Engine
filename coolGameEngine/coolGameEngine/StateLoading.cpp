#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>

#include "SFML\Window.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "BaseState.h"
#include "StateLoading.h"
#include "StateStatic.h"
#include "StateReInit.h"
#include "StateMenu.h"
#include "StateLevel.h"
#include "Property.h"
#include "Entity.h"
#include "BaseController.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Render.h"


StateLoading::StateLoading()
{
	//Sets defaults.
	id = "Loading";
	number = 0;
	systemManager = nullptr;
	assetManager = nullptr;

	//Reads in the filenames and substrings.
	std::ifstream file("file.txt");
	if (file.is_open())
	{
		std::string temp;
		while (!file.eof())
		{
			file >> temp;
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


StateLoading::StateLoading(SystemManager *s, AssetManager *a)
{
	//Sets defaults.
	id = "Loading";
	number = 0;
	systemManager = s;
	assetManager = a;

	//Reads in the filenames and substrings.
	std::ifstream file("file.txt");
	if (file.is_open())
	{
		std::string temp;
		while (!file.eof())
		{
			file >> temp;
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


StateLoading::~StateLoading()
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
			filenames.erase(filenames.begin()+i);
			return temp;
		}
	}

	//There are no filenames with this substring name, so it is done.
	substrings.erase(substrings.begin());
	return fileDeterminer();
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


//Initializes all of the other classes that go into the system and asset managers from files.
//Takes in time elapsed and the window.
void StateLoading::update(double totalTime, sf::RenderWindow *window)
{
	//Checks if there are substrings. If there are none, the process is done.
	if (substrings.size() != 0)
	{
		std::string tempId;
		std::string filename;
		std::string word;
		std::string type;

		int lineNumber = 1; //The line number of the file
		int wordNumber = 1; //Determines which word of the line (1st, 2nd, 3rd, words in a line or more)

		//Determine the file to parse data from.
		filename = fileDeterminer();

		//Open the proper file.
		std::ifstream file (filename);

		//Determine the operation.
		//If it is an image.
		if (substrings.at(0) == "png")
		{
			sf::Image *temp = new sf::Image;
			temp->loadFromFile(filename);
			assetManager->add(temp);
			assetManager->addImageString(filename);
		}

		//If it is a property.
		else if (substrings.at(0) == "property")
		{
			std::vector<std::string> data;

			//Read entire file
			while (!file.eof())
			{
				file >> word;
				
				//Read until the end of the line
				while (word != ";")
				{
					if (lineNumber == 1)
						id = word;
					if (lineNumber == 2)
						type = word;
					if (lineNumber > 2)
						data.push_back(word);

					file >> word;
				}

				lineNumber++;
			}

			//Create.
			//Property is the parent class to the property class.

			Property *temp;
		
			//Create a property based on the type.
			if (type == "int")
			{
				temp = new Property("int");

				for (int i = 0; i < data.size(); i++)
					temp->addData(std::stoi(data.at(i)));
			}
			else if (type == "char")
			{
				temp = new Property("char");

				for (int i = 0; i < data.size(); i++)
					temp->addData(data.at(i).c_str());
			}

			else if (type == "double")
			{
				temp = new Property("double");

				for(int i = 0; i < data.size(); i++)
					temp->addData(std::stod(data.at(i)));
			}

			else if (type == "float")
			{
				temp = new Property("float");

				for(int i = 0; i < data.size(); i++)
					temp->addData(std::stof(data.at(i)));
			}

			else if (type == "bool")
			{
				temp = new Property("bool");

				bool tOrF = false;
				if (data.at(0) == "true")
					tOrF = true;

				for (int i = 0; i < data.size(); i++)
					temp->addData(tOrF);
			}

			else if (type == "string")
			{
				temp = new Property("string");

				for (int i = 0; i < data.size(); i++)
					temp->addData(data.at(i));
			}

			else if (type == "Entity")
			{
				temp = new Property("Entity");

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
					temp->addData(systemManager->getMaterial(data.at(i)));
			}

			else if (type == "Texture")
			{
				temp = new Property("Texture");

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
					temp->addData(assetManager->getTexture(std::stoi(data.at(i))));
			}

			else if (type == "Image")
			{
				temp = new Property("Image");

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
					temp->addData(assetManager->getTexture(stoi(data.at(i))));
			}

			else if (type == "Sound")
			{
				temp = new Property("Sound");

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
					temp->addData(assetManager->getSound(data.at(i)));
			}
			
			else if(type == "Sprite")
			{
				temp = new Property("Sprite");

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					sf::Sprite *sprite = new sf::Sprite();
					temp->addData(sprite);
				}
			}

			else if (type == "CircleShape")
			{
				temp = new Property("Shape");

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					sf::CircleShape *shape = new sf::CircleShape();
					temp->addData(shape);
				}
			}

			else if (type == "ConvexShape")
			{
				temp = new Property("Shape");

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					sf::ConvexShape *shape = new sf::ConvexShape();
					temp->addData(shape);
				}
			}

			else if (type == "RectangleShape")
			{
				temp = new Property("RectangleShape");

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					sf::RectangleShape *shape = new sf::RectangleShape();
					temp->addData(shape);
				}
			}

			else if(type == "Text")
			{
				temp = new Property("Text");

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					sf::Text *text = new sf::Text();
					temp->addData(text);
				}
			}
			
			else
			{
				temp = new Property("string");

				for (int i = 0; i < data.size(); i++)
					temp->addData(data.at(i));
			}

			//Edit.
			temp->setId(id);

			//Store.
			systemManager->add(temp);

		}
		//If it is an entity.
		else if (substrings.at(0) == "entity")
		{
			//The first vector is for holding all properties. The second is for holding tempId and data of the properties.
			std::vector<std::vector<std::string>>properties;

			//Read in data.
			while (!file.eof())
			{
				file >> word;
				while (word != ";") //Read until the end of the line
				{
					if (lineNumber == 1)
						id = word;
					//If it is reading in properties...
					if (lineNumber > 1)
					{
						//If it is the beginning of a new line...
						if (wordNumber == 1)
						{
							//Push back a new string vector for the property.
							std::vector<std::string> temp;
							properties.push_back(temp);
						}
						properties.at(lineNumber - 1).push_back(word);
					}

					file >> word;
					wordNumber++;
				}
				lineNumber++;
				wordNumber = 1;
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
							Property *component = systemManager->getComponent(properties.at(y).at(x));
							//Stores the new property in systemManager.
							systemManager->add(component);
							//Links the Entity to the property.
							temp->add(component);
						}
						//Change Data.
						else
						{
							//Needs to be converted to the proper type.
							if (type == "int")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(std::stoi(properties.at(y).at(x)));
							}

							else if (type == "char")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(properties.at(y).at(x).c_str());
							}

							else if (type == "double")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(std::stod(properties.at(y).at(x)));
							}

							else if (type == "float")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(std::stof(properties.at(y).at(x)));
							}

							else if (type == "bool")
							{
								bool tOrF = false;

								if (properties.at(y).at(x) == "true")
									tOrF = true;

								temp->getComponent(properties.at(y).at(x))->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(tOrF);
							}

							else if (type == "string")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(properties.at(y).at(x));
							}

							else if (type == "Entity")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								temp->getComponent(properties.at(y).at(x))->addData(systemManager->getMaterial(properties.at(y).at(x)));
							}

							else if (type == "Texture")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								temp->getComponent(properties.at(y).at(x))->addData(assetManager->getTexture(std::stoi(properties.at(y).at(x))));
							}

							else if (type == "Image")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								temp->getComponent(properties.at(y).at(x))->addData(assetManager->getImage(properties.at(y).at(x)));
							}

							else if (type == "Sound")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								temp->getComponent(properties.at(y).at(x))->addData(assetManager->getSound(properties.at(y).at(x)));
							}

							else if (type == "Sprite")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::Sprite sprite;
								temp->getComponent(properties.at(y).at(x))->addData(sprite);
							}

							else if (type == "CircleShape")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::CircleShape shape;
								temp->getComponent(properties.at(y).at(x))->addData(shape);
							}

							else if (type == "ConvexShape")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::ConvexShape shape;
								temp->getComponent(properties.at(y).at(x))->addData(shape);
							}

							else if (type == "RectangleShape")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::RectangleShape shape;
								temp->getComponent(properties.at(y).at(x))->addData(shape);
							}

							else if (type == "Text")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::Text text;
								temp->getComponent(properties.at(y).at(x))->addData(text);
							}
							else
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								temp->getComponent(properties.at(y).at(x))->addData(properties.at(y).at(x));
							}
						}
					}
					else
					{
						//Link the property.
						temp->add(systemManager->getComponent(properties.at(y).at(x)));
					}
				}
			}

			//Store.
			systemManager->add(temp);
		}
		//If it is a controller.
		else if (substrings.at(0) == "controller")
		{
			std::vector<std::string> properties;

			//Read in data
			while (!file.eof())
			{
				file >> word;

				//Read until the end of the line
				while (word != ";") 
				{
					if (lineNumber == 1)
						tempId = word;

					if (lineNumber > 2)
						properties.push_back(word);

					file >> word;
				}
				lineNumber++;
			}
			
			BaseController *temp;

			//Create a new controller based on tempId.
			if (tempId == "Render")
			{
				temp = new Render();
				initializeController(temp, tempId, properties);
			}
		}

		//If it is a state.
		else if (substrings.at(0) == "state")
		{
			std::string number;
			int intNumber;

			//read data and take in values. Includes tempId.
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

			BaseState *temp;

			//Determine the state.
			//Does this work?
			intNumber = static_cast<int>(atoi(number.c_str()) - 48);

			//Create
			switch (intNumber)
			{
			case 0:
				temp = new StateLoading(systemManager, assetManager);
				initializeState(temp, tempId, intNumber);
				break;
			case 1:
				temp = new StateStatic(systemManager, assetManager);
				initializeState(temp, tempId, intNumber);
				break;
			case 2:
				temp = new StateMenu(systemManager, assetManager);
				initializeState(temp, tempId, intNumber);
				break;
			case 3:
				temp = new StateLevel(systemManager, assetManager);
				initializeState(temp, tempId, intNumber);
				break;
			case 4:
				temp = new StateReInit(systemManager, assetManager);
				initializeState(temp, tempId, intNumber);
				break;
			}
		}
	}
	//the process is done.
	else
	{
		BaseState::changeState(this, "Welcome");
	}

}


void StateLoading::initializeController(BaseController *temp, std::string tempId, std::vector<std::string> properties)
{
	//Get required properties.
	std::vector<Property *> *components = new std::vector<Property *>;
	for (int i = 0; i < properties.size(); i++)
		components->push_back(systemManager->getComponent(properties.at(i)));

	//Set required properties.
	temp->setRequiredProperties(components);

	systemManager->add(temp);
}


void StateLoading::initializeState(BaseState *temp, std::string tempId, int intNumber)
{
	//Edit
	temp->setId(id);
	temp->setNumber(intNumber);
	temp->setMaterial(systemManager->getMaterial(temp));

	//Store
	systemManager->add(temp);
}
