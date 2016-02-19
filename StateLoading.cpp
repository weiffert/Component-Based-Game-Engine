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
	iteration = 0;

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
		if (filenames.at(i).find(substrings.at(iteration)) != std::string::npos)
		{
			std::string temp = filenames.at(i);
			filenames.erase(i);
			return temp;
		}
	}

	iteration++;

	return nullptr;
}


//Sorts the substrings into a particular order.
void StateLoading::substringSorter()
{
	for (int i = 0; i < substrings.size(); i++)
	{
		std::string first;
		switch (i)
		{
		case 1:
			first = "property";
			break;
		case 2:
			first = "entity";
			break;
		case 3:
			first = "controller";
			break;
		case 4:
			first = "state";
			break;
		default:
			first = "default";
		}

		if (substrings.at(1) != first)
		{
			for (int j = i; j < substrings.size(); i++)
			{
				if (substrings.at(j) == first)
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

	std::string id;
	std::string filename;
	filename = fileDeterminer();

	switch (substrings.at(iteration))
	{
	case "property":
		vector<std::string> data;
		std::string type;

		//Read data and take in these values. Includes id.

		BaseComponent *temp = new Property < type >() ; //Not sure about the type thing yet.
		temp->setId(id);
		for (int i = 0; i < data.size(); i++)
			temp->addData(data.at(i));

		systemManager.add(temp);

		break;
	case "entity":
		vector<vector<std::string>>properties;	//The first vector is for holding all properties. The second is for holding id and data of the properties.

		//Read data and take in these values. Includes id.

		Entity *temp = new Entity();
		temp->setId(id);

		for (int y = 0; y < properties.size(); y++)
		{
			for (int x = 0; x < properties.at(y).size(); x++)
			{
				if (x == 0)
					temp->add(systemManager->getComponent(properties.at(y).at(x)));
				else
					//Needs to be converted to the proper type.
					temp->getComponent(properties.at(y).at(0))->changeData(/*properties.at(y).at(x)*/, x - 1);
			}
		}

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

		intNumber = static_cast<int>(number)-48;

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

		temp->setId(id);
		temp->setNumber(intNumber);
		temp->setMaterial(systemManager->getMaterial(temp));

		systemManager.add(temp);

		break;

	default:
		return -1;
	}
}


void StateLoading::render(double lag, sf::RenderWindow)
{
}
