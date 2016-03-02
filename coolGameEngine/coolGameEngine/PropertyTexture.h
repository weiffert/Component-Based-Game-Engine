#pragma once
#include "BaseComponent.h"

#include "SFML\Graphics.hpp"

class PropertyTexture : 
	public BaseComponent
{
public:
	PropertyTexture();
	~PropertyTexture();

	//Returns the data as a vector.
	std::vector<sf::Texture> getData();
	sf::Texture getData(int);

	//Edit the data.
	void addData(sf::Texture);
	void deleteData();
	void deleteData(sf::Texture);
	void deleteDataPosition(int);
	void changeData(sf::Texture, int);

private:
	std::vector<sf::Texture> data;
};

