#include "stdafx.h"

#include <vector>
#include <fstream>
#include <string>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

#include "StateReInit.h"
#include "BaseState.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "StateLoading.h"
#include "Entity.h"
#include "Property.h"



//SFML includes
StateReInit::StateReInit()
{
	//Sets defaults.
	id = "End";
	number = 4;
	systemManager = nullptr;
	assetManager = nullptr;

	
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


StateReInit::StateReInit(SystemManager *s, AssetManager *a)
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


StateReInit::~StateReInit()
{
}


//Determines the proper file to use based off of the current substring.
//Deletes the filename once it has been determined. Deletes the substring after all of its files have been used.
std::string StateReInit::fileDeterminer()
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
void StateReInit::substringSorter()
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


void StateReInit::update(double totalTime, sf::RenderWindow* window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
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
			Property *temp = systemManager->getComponent(id);

			temp->deleteData();
			if (type == "int")
			{
				for (int i = 0; i < data.size(); i++)
				{
					int integer = std::stoi(data.at(i));
					temp->addData(&integer);
				}
			}
			else if (type == "char")
			{
				for (int i = 0; i < data.size(); i++)
				{
					char character = data.at(i).at(0);
					temp->addData(&character);
				}
			}

			else if (type == "double")
			{
				for (int i = 0; i < data.size(); i++)
				{
					double reals = std::stod(data.at(i));
					temp->addData(&reals);
				}
			}

			else if (type == "float")
			{
				for (int i = 0; i < data.size(); i++)
				{
					float smallerReals = std::stof(data.at(i));
					temp->addData(&smallerReals);
				}
			}

			else if (type == "bool")
			{
				bool tOrF = false;
				if (data.at(0) == "true")
					tOrF = true;

				for (int i = 0; i < data.size(); i++)
					temp->addData(&tOrF);
			}

			else if (type == "string")
			{
				for (int i = 0; i < data.size(); i++)
					temp->addData(&(data.at(i)));
			}

			else if (type == "Entity")
			{
				for (int i = 0; i < data.size(); i++)
					temp->addData(systemManager->getMaterial(data.at(i)));

			}

			else if (type == "Texture")
			{
				//Get the proper data from the tempId in the file.

				sf::Texture *texture = nullptr;

				for (int i = 0; i < data.size(); i++)
				{
					if (data.at(i) == "loadFromFile")
					{
						texture->loadFromFile(data.at(++i));
					}
					else if (data.at(i) == "create")
					{
						texture->create(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
					}
				}

				assetManager->add(texture);
				temp->addData(texture);
			}

			else if (type == "Image")
			{
				sf::Image *image = nullptr;
				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					if (data.at(i) == "loadFromFile")
					{
						image->loadFromFile(data.at(++i));
					}
				}

				assetManager->add(image);
				temp->addData(image);
			}

			///FIXXXXXXXXXXX
			else if (type == "Sound")
			{
				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					sf::Sound *sound = assetManager->getSound(BaseState::conversionInt(data.at(i)));
					temp->addData(sound);
				}
			}
			///FIXXXXXXXXXXXX

			else if (type == "Sprite")
			{
				sf::Sprite *sprite = nullptr;

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					if (data.at(i) == "setTexture")
					{
						sprite->setTexture(*(assetManager->getTexture(BaseState::conversionInt(data.at(++i)))));
					}
					else if (data.at(i) == "setTextureRect")
					{
						sf::IntRect r(0, 0, BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						sprite->setTextureRect(r);
					}
					else if (data.at(i) == "setColor")
					{
						sf::Color c(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						sprite->setColor(c);
					}
					else if (data.at(i) == "setPosition")
					{
						sprite->setPosition(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
					}
					else if (data.at(i) == "setRotation")
					{
						sprite->setRotation(BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setScale")
					{
						sprite->setScale(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setOrigin")
					{
						sprite->setOrigin(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
				}

				temp->addData(sprite);
			}

			else if (type == "CircleShape")
			{
				sf::CircleShape *shape = nullptr;

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					if (data.at(i) == "setRadius")
					{
						shape->setRadius(BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setPointCount")
					{
						shape->setPointCount(BaseState::conversionInt(data.at(++i)));
					}
					else if (data.at(i) == "setTexture")
					{
						shape->setTexture(assetManager->getTexture(BaseState::conversionInt(data.at(++i))));
					}
					else if (data.at(i) == "setTextureRect")
					{
						sf::IntRect r(0, 0, BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						shape->setTextureRect(r);
					}
					else if (data.at(i) == "setFillColor")
					{
						sf::Color c(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						shape->setFillColor(c);
					}
					else if (data.at(i) == "setOutlineColor")
					{
						sf::Color c(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						shape->setOutlineColor(c);
					}
					else if (data.at(i) == "setPosition")
					{
						shape->setPosition(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
					}
					else if (data.at(i) == "setRotation")
					{
						shape->setRotation(BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setScale")
					{
						shape->setScale(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setOrigin")
					{
						shape->setOrigin(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
				}

				temp->addData(shape);
			}

			else if (type == "ConvexShape")
			{
				sf::ConvexShape *shape = nullptr;

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					if (data.at(i) == "setPoint")
					{
						shape->setPoint(BaseState::conversionInt(data.at(++i)), sf::Vector2f(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i))));
					}
					else if (data.at(i) == "setPointCount")
					{
						shape->setPointCount(BaseState::conversionInt(data.at(++i)));
					}
					else if (data.at(i) == "setTexture")
					{
						shape->setTexture(assetManager->getTexture(BaseState::conversionInt(data.at(++i))));
					}
					else if (data.at(i) == "setTextureRect")
					{
						sf::IntRect r(0, 0, BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						shape->setTextureRect(r);
					}
					else if (data.at(i) == "setFillColor")
					{
						sf::Color c(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						shape->setFillColor(c);
					}
					else if (data.at(i) == "setOutlineColor")
					{
						sf::Color c(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						shape->setOutlineColor(c);
					}
					else if (data.at(i) == "setPosition")
					{
						shape->setPosition(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
					}
					else if (data.at(i) == "setRotation")
					{
						shape->setRotation(BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setScale")
					{
						shape->setScale(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setOrigin")
					{
						shape->setOrigin(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
				}

				temp->addData(shape);
			}

			else if (type == "RectangleShape")
			{
				sf::RectangleShape *shape = nullptr;

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					if (data.at(i) == "setSize")
					{
						sf::Vector2f v(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
						shape->setSize(v);
					}
					else if (data.at(i) == "setTexture")
					{
						shape->setTexture(assetManager->getTexture(BaseState::conversionInt(data.at(++i))));
					}
					else if (data.at(i) == "setTextureRect")
					{
						sf::IntRect r(0, 0, BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						shape->setTextureRect(r);
					}
					else if (data.at(i) == "setFillColor")
					{
						sf::Color c(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						shape->setFillColor(c);
					}
					else if (data.at(i) == "setOutlineColor")
					{
						sf::Color c(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						shape->setOutlineColor(c);
					}
					else if (data.at(i) == "setOutlineThickness")
					{
						shape->setOutlineThickness(BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setPosition")
					{
						shape->setPosition(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
					}
					else if (data.at(i) == "setRotation")
					{
						shape->setRotation(BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setScale")
					{
						shape->setScale(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setOrigin")
					{
						shape->setOrigin(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
				}

				temp->addData(shape);
			}

			else if (type == "Text")
			{
				sf::Text *text = nullptr;

				//Get the proper data from the tempId in the file.
				for (int i = 0; i < data.size(); i++)
				{
					if (data.at(i) == "setString")
					{
						text->setString(data.at(++i));
					}
					else if (data.at(i) == "setFont")
					{
						sf::Font f;
						f.loadFromFile(data.at(++i));

						text->setFont(f);
					}
					else if (data.at(i) == "setCharacterSize")
					{
						text->setCharacterSize(BaseState::conversionInt(data.at(++i)));
					}
					else if (data.at(i) == "setStyle")
					{
						if (data.at(++i) == "Bold")
						{
							text->setStyle(sf::Text::Bold);
						}
						else if (data.at(i) == "Italic")
						{
							text->setStyle(sf::Text::Italic);
						}
						else if (data.at(i) == "Regular")
						{
							text->setStyle(sf::Text::Regular);
						}
						else if (data.at(i) == "StrikeThrough")
						{
							text->setStyle(sf::Text::StrikeThrough);
						}
						else if (data.at(i) == "Underlined")
						{
							text->setStyle(sf::Text::Underlined);
						}
					}
					else if (data.at(i) == "setColor")
					{
						sf::Color c(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
						text->setColor(c);
					}
					else if (data.at(i) == "setPosition")
					{
						text->setPosition(BaseState::conversionInt(data.at(++i)), BaseState::conversionInt(data.at(++i)));
					}
					else if (data.at(i) == "setRotation")
					{
						text->setRotation(BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setScale")
					{
						text->setScale(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
					else if (data.at(i) == "setOrigin")
					{
						text->setOrigin(BaseState::conversionFloat(data.at(++i)), BaseState::conversionFloat(data.at(++i)));
					}
				}

				temp->addData(text);
			}

			else
			{
				for (int i = 0; i < data.size(); i++)
					temp->addData(&(data.at(i)));
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
							Property *component = systemManager->getComponent(properties.at(y).at(x));
							systemManager->add(component);
							temp->remove(component);
							temp->add(component);
						}
						//Change Data.
						else
						{
							//Needs to be converted to the proper type.
							if (type == "int")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								int integer = std::stoi(properties.at(y).at(x));
								temp->getComponent(properties.at(y).at(x))->addData(&integer);
							}

							else if (type == "char")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								char character = properties.at(y).at(x).at(0);
								temp->getComponent(properties.at(y).at(x))->addData(&character);
							}

							else if (type == "double")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								double doubler = std::stod(properties.at(y).at(x));
								temp->getComponent(properties.at(y).at(x))->addData(&doubler);
							}

							else if (type == "float")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								float floater = std::stof(properties.at(y).at(x));
								temp->getComponent(properties.at(y).at(x))->addData(&floater);
							}

							else if (type == "bool")
							{
								bool tOrF = false;

								if (properties.at(y).at(x) == "true")
									tOrF = true;

								temp->getComponent(properties.at(y).at(x))->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(&tOrF);
							}

							else if (type == "string")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								temp->getComponent(properties.at(y).at(x))->addData(&(properties.at(y).at(x)));
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
								temp->getComponent(properties.at(y).at(x))->addData(assetManager->getSound(std::stoi(properties.at(y).at(x))));
							}

							else if (type == "Sprite")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::Sprite *sprite = new sf::Sprite;
								temp->getComponent(properties.at(y).at(x))->addData(sprite);
							}

							else if (type == "CircleShape")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::CircleShape *shape = new sf::CircleShape;
								temp->getComponent(properties.at(y).at(x))->addData(shape);
							}

							else if (type == "ConvexShape")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::ConvexShape *shape = new sf::ConvexShape;
								temp->getComponent(properties.at(y).at(x))->addData(shape);
							}

							else if (type == "RectangleShape")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::RectangleShape *shape = new sf::RectangleShape;
								temp->getComponent(properties.at(y).at(x))->addData(shape);
							}

							else if (type == "Text")
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								sf::Text *text = new sf::Text;
								temp->getComponent(properties.at(y).at(x))->addData(text);
							}
							else
							{
								temp->getComponent(properties.at(y).at(x))->deleteData();
								//Get the proper data from the tempId in the file.
								temp->getComponent(properties.at(y).at(x))->addData(&(properties.at(y).at(x)));
							}
						}
					}
					else //Link the property.
						temp->add(systemManager->getComponent(properties.at(y).at(x)));
				}
			}
		}
	}
}
