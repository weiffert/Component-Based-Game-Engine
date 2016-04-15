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
					substrings.push_back(temp);
				}
			}
		}
	}

	//Sorts the substrings into the proper order.
	//substringSorter();
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
					substrings.push_back(temp);
				}
			}
		}
	}

	//Sorts the substrings into the proper order.
	//substringSorter();
}


StateLoading::~StateLoading()
{
}


//Determines the proper file to use based off of the current substring.
//Deletes the filename once it has been determined. Deletes the substring after all of its files have been used.
std::string StateLoading::fileDeterminer()
{
	if (substrings.size() > 0)
	{
		//Passes through all of the filenames.
		for (int i = 0; i < filenames.size(); i++)
		{
			//If the base substring is found in the filename...
			if (filenames.at(i).find(substrings.at(0)) != std::string::npos)
			{
				std::string temp = filenames.at(i);
				filenames.erase(filenames.begin() + i);
				return temp;
			}
		}

		if (substrings.size() > 0)
		{
			//There are no filenames with this substring name, so it is done.
			substrings.erase(substrings.begin());
			return fileDeterminer();
		}
	}

	return "default";
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
			sub = "state";
			break;
		default:
			sub = "default";
		}

		//If it is not in the proper position...
		if (substrings.at(i) != sub)
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
std::string StateLoading::update(double totalTime, sf::RenderWindow *window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}


	//Checks if there are substrings. If there are none, the process is done.
	while (substrings.size() > 0)
	{
		std::string tempId;
		std::string filename;
		std::string word;
		std::string type;

		int lineNumber = 1; //The line number of the file
		int wordNumber = 1; //Determines which word of the line (1st, 2nd, 3rd, words in a line or more)

		//Determine the file to parse data from.
		filename = fileDeterminer();

		if (substrings.size() > 0)
		{

			//Open the proper file.
			std::ifstream file(filename);

			//Determine the operation.
			//If it is an image.

			if (substrings.at(0) == "png")
			{
				sf::Image *temp = new sf::Image;
				if (!temp->loadFromFile(filename))
					std::cout << "Failed to load " << filename << std::endl;
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
							tempId = word;
						if (lineNumber == 2)
							type = word;
						if (lineNumber > 2)
							data.push_back(word);

						file >> word;
					}

					lineNumber++;
				}

				//Create.
				Property *temp = nullptr;

				//Create a property based on the type.
				if (type == "int")
				{
					temp = new Property("int");

					for (int i = 0; i < data.size(); i++)
					{
						int integer = std::stoi(data.at(i));
						temp->addData(integer);
					}
				}
				else if (type == "char")
				{
					temp = new Property("char");

					for (int i = 0; i < data.size(); i++)
					{
						char character = data.at(i).at(0);
						temp->addData(character);
					}
				}

				else if (type == "double")
				{
					temp = new Property("double");

					for (int i = 0; i < data.size(); i++)
					{
						double reals = std::stod(data.at(i));
						temp->addData(reals);
					}
				}

				else if (type == "float")
				{
					temp = new Property("float");

					for (int i = 0; i < data.size(); i++)
					{
						float smallerReals = std::stof(data.at(i));
						temp->addData(smallerReals);
					}
				}

				else if (type == "bool")
				{
					temp = new Property("bool");

					bool tOrF = false;

					for (int i = 0; i < data.size(); i++)
					{
						if (data.at(i).find("true") != std::string::npos)
							tOrF = true;
						temp->addData(tOrF);
					}
				}

				else if (type == "string")
				{
					temp = new Property("string");

					for (int i = 0; i < data.size(); i++)
						temp->addData(data.at(i));
				}

				else if (type == "Entity")
				{
					//Save the pointer
					temp = new Property("Entity");
					entityProperties.push_back(temp);

					//Save the data.
					std::vector<std::string> vecTemp;
					for (int i = 0; i < data.size(); i++)
					{
						vecTemp.push_back(data.at(i));
					}

					entityPropertiesData.push_back(vecTemp);
				}

				else if (type == "Texture")
				{
					temp = new Property("Texture");

					//Get the proper data from the tempId in the file.

					sf::Texture *texture = new sf::Texture;

					for (int i = 0; i < data.size(); i++)
					{
						if (data.at(i) == "loadFromFile")
						{
							if (!texture->loadFromFile(data.at(++i)))
								std::cout << "Failed to load image " << data.at(i) << std::endl;
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
					temp = new Property("Image");

					sf::Image *image = new sf::Image;
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

				else if (type == "SoundBuffer")
				{
					temp = new Property("SoundBuffer");

					sf::SoundBuffer *buffer = new sf::SoundBuffer;
					//Get the proper data from the tempId in the file.
					for (int i = 0; i < data.size(); i++)
					{
						if (data.at(i) == "loadFromFile")
						{
							if (!buffer->loadFromFile(data.at(++i)))
								std::cout << "Failed to load " << data.at(i) << std::endl;
						}
						assetManager->add(buffer);
						temp->addData(buffer);
					}
				}

				else if (type == "Sound")
				{
					temp = new Property("Sound");

					sf::Sound *sound = new sf::Sound;
					//Get the proper data from the tempId in the file.
					for (int i = 0; i < data.size(); i++)
					{
						if (data.at(i) == "setBuffer")
						{
							sound->setBuffer(*(assetManager->getSoundBuffer(BaseState::conversionInt(data.at(++i)))));
						}

					}
					assetManager->add(sound);
					temp->addData(sound);

				}

				else if (type == "Sprite")
				{
					temp = new Property("Sprite");

					sf::Sprite *sprite = new sf::Sprite;

					//Get the proper data from the tempId in the file.
					for (int i = 0; i < data.size(); i++)
					{
						if (data.at(i) == "setTexture")
						{
							sf::Texture *texture = new sf::Texture;
							if (!texture->loadFromFile(data.at(++i)))
								std::cout << "Failed to load " << data.at(i) << std::endl;
							sprite->setTexture(*texture);
							assetManager->add(texture);
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
					temp = new Property("CircleShape");

					sf::CircleShape *shape = new sf::CircleShape;

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
							sf::Texture *texture = new sf::Texture;
							if (!texture->loadFromFile(data.at(++i)))
								std::cout << "Failed to load " << data.at(i) << std::endl;
							shape->setTexture(texture, false);
							assetManager->add(texture);
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
					temp = new Property("ConvexShape");

					sf::ConvexShape *shape = new sf::ConvexShape;

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
							sf::Texture *texture = new sf::Texture;
							if (!texture->loadFromFile(data.at(++i)))
								std::cout << "Failed to load " << data.at(i) << std::endl;
							shape->setTexture(texture, false);
							assetManager->add(texture);
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
					temp = new Property("RectangleShape");

					sf::RectangleShape *shape = new sf::RectangleShape;

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
							sf::Texture *texture = new sf::Texture;
							if (!texture->loadFromFile(data.at(++i)))
								std::cout << "Failed to load " << data.at(i) << std::endl;
							shape->setTexture(texture, false);
							assetManager->add(texture);
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
					temp = new Property("Text");

					sf::Text *text = new sf::Text;

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

				else if (type == "Color")
				{
					temp = new Property("Color");

					sf::Color *c = nullptr;
					for (int i = 0; i < data.size(); i++)
					{
						int r = BaseState::conversionInt(data.at(i++));
						int g = BaseState::conversionInt(data.at(i++));
						int b = BaseState::conversionInt(data.at(i++));
						c = new sf::Color(r, g, b);
					}
					temp->addData(c);
				}

				else
				{
					temp = new Property("string");

					for (int i = 0; i < data.size(); i++)
						temp->addData(&(data.at(i)));
				}

				//Edit.
				temp->setId(tempId);

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
							tempId = word;
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
							properties.at(lineNumber - 2).push_back(word);
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
				temp->setId(tempId);
				//Loop for the vector.
				for (int y = 0; y < properties.size(); y++)
				{
					//If there is data.
					if (properties.at(y).size() > 1)
					{
						Property *componentTemp = systemManager->getComponent(properties.at(y).at(0));
						type = componentTemp->getType();
						tempId = componentTemp->getId();

						Property *component = nullptr;

						//Create a property based on the type.
						if (type == "int")
						{
							component = new Property("int");

							for (int i = 1; i < properties.at(y).size(); i++)
							{
								int integer = std::stoi(properties.at(y).at(i));
								component->addData(integer);
							}
						}
						else if (type == "char")
						{
							component = new Property("char");

							for (int i = 1; i < properties.at(y).size(); i++)
							{
								char character = properties.at(y).at(i).at(0);
								component->addData(character);
							}
						}

						else if (type == "double")
						{
							component = new Property("double");

							for (int i = 1; i < properties.at(y).size(); i++)
							{
								double reals = std::stod(properties.at(y).at(i));
								component->addData(reals);
							}
						}

						else if (type == "float")
						{
							component = new Property("float");

							for (int i = 1; i < properties.at(y).size(); i++)
							{
								float smallerReals = std::stof(properties.at(y).at(i));
								component->addData(smallerReals);
							}
						}

						else if (type == "bool")
						{
							component = new Property("bool");

							bool tOrF = false;
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i).find("true") != std::string::npos)
									tOrF = true;
								component->addData(tOrF);
							}
						}

						else if (type == "string")
						{
							component = new Property("string");

							for (int i = 1; i < properties.at(y).size(); i++)
								component->addData(properties.at(y).at(i));
						}

						else if (type == "Entity")
						{
							//Save the pointer
							component = new Property("Entity");
							entityProperties.push_back(component);

							//Save the data.
							std::vector<std::string> vecTemp;
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								vecTemp.push_back(properties.at(y).at(i));
							}

							entityPropertiesData.push_back(vecTemp);

						}

						else if (type == "Texture")
						{
							component = new Property("Texture");

							//Get the proper properties.at(y) from the tempId in the file.

							sf::Texture *texture = new sf::Texture;

							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i) == "loadFromFile")
								{
									if (!texture->loadFromFile(properties.at(y).at(++i)))
										std::cout << "Failed to load image " << properties.at(y).at(i) << std::endl;
								}
								else if (properties.at(y).at(i) == "create")
								{
									texture->create(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
								}
							}

							assetManager->add(texture);
							component->addData(texture);
						}

						else if (type == "Image")
						{
							component = new Property("Image");

							sf::Image *image = new sf::Image;
							//Get the proper properties.at(y) from the tempId in the file.
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i) == "loadFromFile")
								{
									image->loadFromFile(properties.at(y).at(++i));
								}
							}

							assetManager->add(image);
							component->addData(image);
						}

						else if (type == "SoundBuffer")
						{
							component = new Property("SoundBuffer");

							sf::SoundBuffer *buffer = new sf::SoundBuffer;
							//Get the proper properties.at(y) from the tempId in the file.
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i) == "loadFromFile")
								{
									buffer->loadFromFile(properties.at(y).at(++i));
								}
								assetManager->add(buffer);
								component->addData(buffer);
							}
						}

						else if (type == "Sound")
						{
							component = new Property("Sound");

							sf::Sound *sound = new sf::Sound;
							//Get the proper properties.at(y) from the tempId in the file.
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i) == "setBuffer")
								{
									sound->setBuffer(*(assetManager->getSoundBuffer(BaseState::conversionInt(properties.at(y).at(++i)))));
								}

							}
							assetManager->add(sound);
							component->addData(sound);

						}

						else if (type == "Sprite")
						{
							component = new Property("Sprite");

							sf::Sprite *sprite = new sf::Sprite;

							//Get the proper properties.at(y) from the tempId in the file.
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i) == "setTexture")
								{
									sf::Texture *texture = new sf::Texture;
									if (!texture->loadFromFile(properties.at(y).at(++i)))
										std::cout << "Failed to load " << properties.at(y).at(i) << std::endl;
									sprite->setTexture(*texture);
									assetManager->add(texture);
								}
								else if (properties.at(y).at(i) == "setTextureRect")
								{
									sf::IntRect r(0, 0, BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									sprite->setTextureRect(r);
								}
								else if (properties.at(y).at(i) == "setColor")
								{
									sf::Color c(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									sprite->setColor(c);
								}
								else if (properties.at(y).at(i) == "setPosition")
								{
									float f1 = BaseState::conversionFloat(properties.at(y).at(++i));
									float f2 = BaseState::conversionFloat(properties.at(y).at(++i));
									sprite->setPosition(f1, f2);
								}
								else if (properties.at(y).at(i) == "setRotation")
								{
									sprite->setRotation(BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setScale")
								{
									sprite->setScale(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setOrigin")
								{
									sprite->setOrigin(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
							}

							component->addData(sprite);
						}

						else if (type == "CircleShape")
						{
							component = new Property("CircleShape");

							sf::CircleShape *shape = new sf::CircleShape;

							//Get the proper properties.at(y) from the tempId in the file.
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i) == "setRadius")
								{
									shape->setRadius(BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setPointCount")
								{
									shape->setPointCount(BaseState::conversionInt(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setTexture")
								{
									sf::Texture *texture = new sf::Texture;
									if (!texture->loadFromFile(properties.at(y).at(++i)))
										std::cout << "Failed to load " << properties.at(y).at(i) << std::endl;
									shape->setTexture(texture, false);
									assetManager->add(texture);
								}
								else if (properties.at(y).at(i) == "setTextureRect")
								{
									sf::IntRect r(0, 0, BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									shape->setTextureRect(r);
								}
								else if (properties.at(y).at(i) == "setFillColor")
								{
									sf::Color c(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									shape->setFillColor(c);
								}
								else if (properties.at(y).at(i) == "setOutlineColor")
								{
									sf::Color c(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									shape->setOutlineColor(c);
								}
								else if (properties.at(y).at(i) == "setPosition")
								{
									shape->setPosition(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setRotation")
								{
									shape->setRotation(BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setScale")
								{
									shape->setScale(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setOrigin")
								{
									shape->setOrigin(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
							}

							component->addData(shape);
						}

						else if (type == "ConvexShape")
						{
							component = new Property("ConvexShape");

							sf::ConvexShape *shape = new sf::ConvexShape;

							//Get the proper properties.at(y) from the tempId in the file.
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i) == "setPoint")
								{
									shape->setPoint(BaseState::conversionInt(properties.at(y).at(++i)), sf::Vector2f(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i))));
								}
								else if (properties.at(y).at(i) == "setPointCount")
								{
									shape->setPointCount(BaseState::conversionInt(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setTexture")
								{
									sf::Texture *texture = new sf::Texture;
									if (!texture->loadFromFile(properties.at(y).at(++i)))
										std::cout << "Failed to load " << properties.at(y).at(i) << std::endl;
									shape->setTexture(texture, false);
									assetManager->add(texture);
								}
								else if (properties.at(y).at(i) == "setTextureRect")
								{
									sf::IntRect r(0, 0, BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									shape->setTextureRect(r);
								}
								else if (properties.at(y).at(i) == "setFillColor")
								{
									sf::Color c(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									shape->setFillColor(c);
								}
								else if (properties.at(y).at(i) == "setOutlineColor")
								{
									sf::Color c(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									shape->setOutlineColor(c);
								}
								else if (properties.at(y).at(i) == "setPosition")
								{
									shape->setPosition(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setRotation")
								{
									shape->setRotation(BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setScale")
								{
									shape->setScale(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setOrigin")
								{
									shape->setOrigin(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
							}

							component->addData(shape);
						}

						else if (type == "RectangleShape")
						{
							component = new Property("RectangleShape");

							sf::RectangleShape *shape = new sf::RectangleShape;

							//Get the proper properties.at(y) from the tempId in the file.
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i) == "setSize")
								{
									sf::Vector2f v(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
									shape->setSize(v);
								}
								else if (properties.at(y).at(i) == "setTexture")
								{
									sf::Texture *texture = new sf::Texture;
									if (!texture->loadFromFile(properties.at(y).at(++i)))
										std::cout << "Failed to load " << properties.at(y).at(i) << std::endl;
									shape->setTexture(texture, false);
									assetManager->add(texture);
								}
								else if (properties.at(y).at(i) == "setTextureRect")
								{
									sf::IntRect r(0, 0, BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									shape->setTextureRect(r);
								}
								else if (properties.at(y).at(i) == "setFillColor")
								{
									sf::Color c(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									shape->setFillColor(c);
								}
								else if (properties.at(y).at(i) == "setOutlineColor")
								{
									sf::Color c(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									shape->setOutlineColor(c);
								}
								else if (properties.at(y).at(i) == "setOutlineThickness")
								{
									shape->setOutlineThickness(BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setPosition")
								{
									shape->setPosition(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setRotation")
								{
									shape->setRotation(BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setScale")
								{
									shape->setScale(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setOrigin")
								{
									shape->setOrigin(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
							}

							component->addData(shape);
						}

						else if (type == "Text")
						{
							component = new Property("Text");

							sf::Text *text = new sf::Text;

							//Get the proper properties.at(y) from the tempId in the file.
							for (int i = 1; i < properties.at(y).size(); i++)
							{
								if (properties.at(y).at(i) == "setString")
								{
									std::string sTemp1 = "";
									std::string sTemp2 = "";

									int increment = 0;

									while (properties.at(y).at(i).find("\"") == std::string::npos)
									{
										if (increment == 0)
										{
											sTemp1 += properties.at(y).at(++i) + " ";
											i++;
											increment++;
										}
										else
										{
											sTemp1 += properties.at(y).at(i++) + " ";
										}
										if (properties.at(y).at(i).find("\"") != std::string::npos)
											sTemp1 += properties.at(y).at(i) + " ";
									}
									
									for (int i = 0; i < sTemp1.size(); i++)
									{
										if (sTemp1.at(i) != '\"')
											sTemp2.push_back(sTemp1.at(i));
									}

									text->setString(sTemp2);
								}
								else if (properties.at(y).at(i) == "setFont")
								{
									sf::Font *f = new sf::Font;
									if (!f->loadFromFile(properties.at(y).at(++i)))
										std::cout << "Failed to load " << properties.at(y).at(i) << std::endl;

									text->setFont(*f);

									assetManager->add(f);
									assetManager->addFontString("Squares");
								}
								else if (properties.at(y).at(i) == "setCharacterSize")
								{
									text->setCharacterSize(BaseState::conversionInt(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setStyle")
								{
									if (properties.at(y).at(++i) == "Bold")
									{
										text->setStyle(sf::Text::Bold);
									}
									else if (properties.at(y).at(i) == "Italic")
									{
										text->setStyle(sf::Text::Italic);
									}
									else if (properties.at(y).at(i) == "Regular")
									{
										text->setStyle(sf::Text::Regular);
									}
									else if (properties.at(y).at(i) == "StrikeThrough")
									{
										text->setStyle(sf::Text::StrikeThrough);
									}
									else if (properties.at(y).at(i) == "Underlined")
									{
										text->setStyle(sf::Text::Underlined);
									}
								}
								else if (properties.at(y).at(i) == "setColor")
								{
									sf::Color c(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
									text->setColor(c);
								}
								else if (properties.at(y).at(i) == "setPosition")
								{
									text->setPosition(BaseState::conversionInt(properties.at(y).at(++i)), BaseState::conversionInt(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setRotation")
								{
									text->setRotation(BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setScale")
								{
									text->setScale(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
								else if (properties.at(y).at(i) == "setOrigin")
								{
									text->setOrigin(BaseState::conversionFloat(properties.at(y).at(++i)), BaseState::conversionFloat(properties.at(y).at(++i)));
								}
							}

							component->addData(text);
						}

						else
						{
							component = new Property("string");

							for (int i = 1; i < properties.at(y).size(); i++)
								component->addData(&(properties.at(y).at(i)));
						}

						component->setId(tempId);

						//Stores the new property in systemManager.
						systemManager->add(component);

						temp->add(component);
					}

					else
					{
						//Link the property.
						temp->add(systemManager->getComponent(properties.at(y).at(0)));
					}
				}

				//Store.
				systemManager->add(temp);
			}

			//If it is a state.
			else if (substrings.at(0) == "state")
			{
				int intNumber;
				std::string number;

				//read data and take in values. Includes tempId.
				while (!file.eof())
				{
					file >> word;

					//Read until the end of the line
					while (word != ";")
					{
						if (lineNumber == 1)
							tempId = word;
						if (lineNumber == 2)
							type = word;
						if (lineNumber == 3)
							number = word;

						file >> word;
					}

					lineNumber++;
				}

				BaseState *temp = nullptr;

				intNumber = BaseState::conversionInt(number);
				//Determine the state.

				//Create
				if (type == "Loading")
				{
					temp = new StateLoading(systemManager, assetManager);
					initializeState(temp, tempId, intNumber);
				}
				else if (type == "Static")
				{
					temp = new StateStatic(systemManager, assetManager);
					initializeState(temp, tempId, intNumber);
				}
				else if (type == "Menu")
				{
					temp = new StateMenu(systemManager, assetManager);
					initializeState(temp, tempId, intNumber);
				}
				else if (type == "Level")
				{
					temp = new StateLevel(systemManager, assetManager);
					initializeState(temp, tempId, intNumber);
				}
				else if (type == "ReInit")
				{
					temp = new StateReInit(systemManager, assetManager);
					initializeState(temp, tempId, intNumber);
				}
			}
		}
	}

	for (int i = 0; i < entityProperties.size(); i++)
	{
		Property *temp = entityProperties.at(i);
		//Get the proper data from the tempId in the file.
		for (int j = 0; j < entityPropertiesData.at(i).size(); j++)
		{
			temp->addData(systemManager->getMaterial(entityPropertiesData.at(i).at(j)));
		}
	}
	//the process is done.
	return "next";
}


void StateLoading::initializeState(BaseState *temp, std::string tempId, int intNumber)
{
	//Edit
	temp->setId(tempId);
	temp->setNumber(intNumber);
	temp->setMaterial(systemManager->getMaterial(temp));

	//Store
	systemManager->add(temp);
}
