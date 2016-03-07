#pragma once
#include <vector>
#include <string>
#include "Entity.h"
#include "SFML\Graphics.hpp"

class Property
{
public:
	//Allows for simpler data initialization.
	Property(std::string);
	~Property();

	//Edit Id
	std::string getId();
	void setId(std::string);

	//Returns the data as a vector.
	template <class T>
	std::vector<T> getData();
	template <class T>
	T getData(int);

	//Edit the data.
	void deleteData();
	void deleteDataPosition(int);

	template <class T>
	void addData(T);

	template <class T>
	void deleteData(T);

	template <class T>
	void changeData(T, int);

private:
	std::string id;
	std::string typeId;
	std::vector<int> dataInt;
	std::vector<double> dataDouble;
	std::vector<float> dataFloat;
	std::vector<char> dataChar;
	std::vector<bool> dataBool;
	std::vector<std::string> dataString;
	std::vector<sf::Image> dataImage;
	std::vector<sf::Texture> dataTexture;
	std::vector<sf::Sprite> dataSprite;
	std::vector<sf::Shape> dataShape;
	std::vector<sf::Text> dataText;
	std::vector<Entity> dataEntity;
};
