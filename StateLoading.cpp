#include "StateLoading.h"
#include "Property.h"
#include "Entity.h"
#include "BaseController.h"
#include "BaseState.h"
//SFML includes


StateLoading::StateLoading(SystemManager *s)
{
	id = "Loading";
	number = 0;
	systemManager = s;

	//read from the file of files document.
		//store filenames in the filenames string.
		//store substrings in the substring string.

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


int StateLoading::update(double totalTime)
{
	if (substrings.size() != 0)
	{
		std::string id;
		std::string filename;

		//Determine the file to parse data from.
		filename = fileDeterminer();

		//Determine the operation.
		switch (substrings.at(0))
		{
		case "property":
			vector<std::string> data;
			std::string type;

			//Read data and take in these values. Includes id.

			//Create.
			BaseComponent *temp = new Property < type >(); //Not sure about the type thing yet.

			//Edit.
			temp->setId(id);
			//Adding data.
			for (int i = 0; i < data.size(); i++)
				temp->addData(data.at(i));

			//Store.
			systemManager.add(temp);

			break;
		case "entity":
			vector<vector<std::string>>properties;	//The first vector is for holding all properties. The second is for holding id and data of the properties.

			//Read data and take in these values. Includes id.

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
							//Needs to be converted to the proper type.
							temp->getComponent(properties.at(y).at(0))->changeData(/*properties.at(y).at(x)*/, x - 1);
					}
					//Link the property.
					else
						temp->add(systemManager->getComponent(properties.at(y).at(x)));
				}
			}

			//Store.
			systemManager.add(temp);

			break;
		case "controller":
			//I am not sure what to put for here.
			break;

		case "state":
			std::string number;
			int intNumber;
			BaseState *temp;

			//read data and take in values. Includes id.

			//Determine the state.
			intNumber = static_cast<int>(number)-48;

			//Create
			switch (number)
			{
			case 1:
				temp = new StateLoading();
				break;
			case 2:
				temp = new StateWelcome();
				break;
			case 3:
				temp = new StateMenu();
				break;
			case 4:
				temp = new StateLevel();
				break;
			case 5:
				temp = new StateEnd();
				break;
			case 6:
				temp = new StatePause();
				break;
			}

			//Edit
			temp->setId(id);
			temp->setNumber(intNumber);
			temp->setMaterial(systemManager->getMaterial(temp));

			//Store
			systemManager.add(temp);
		}

		//The process is not done.
		return 0;
	}

	//the process is done.
	else
	{
		return 1;
	}
}


void StateLoading::render(double lag, sf::RenderWindow)
{
	w.clear;
	for (int i = 0; i < material.size(); i++)
	{
		if (material.at(i)->hasComponent("draw"))
		{
			//Needs to be a drawable.
			w.draw(material.at(i));
		}
	}
	w.display();
}
