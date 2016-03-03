#pragma once
#include "BaseComponent.h"

#include "SFML\Audio.hpp"

class PropertySound :
	public BaseComponent
{
public:
	PropertySound();
	~PropertySound();

	//Returns the data as a vector.
	std::vector<sf::Sound> getData();
	sf::Sound getData(int);

	//Edit the data.
	void addData(sf::Sound);
	virtual void deleteData();
	void deleteData(sf::Sound);
	virtual void deleteDataPosition(int);
	void changeData(sf::Sound, int);

private:
	std::vector<sf::Sound> data;
};

