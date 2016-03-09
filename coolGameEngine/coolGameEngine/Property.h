#pragma once
#include <vector>
#include <string>

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

/*
#include "Entity.h"
*/

class Entity;

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
	template <typename T>
	std::vector<T> getData();

	//template <typename T>
	//T getData(int);

	//Edit the data.
	void deleteData();
	void deleteDataPosition(int);

	template <typename T>
	void addData(T);

	template <typename T>
	void deleteData(T);

	template <typename T>
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
	std::vector<sf::CircleShape> dataCircleShape;
	std::vector<sf::ConvexShape> dataConvexShape;
	std::vector<sf::RectangleShape> dataRectangleShape;
	std::vector<sf::Text> dataText;
	std::vector<Entity> dataEntity;
	std::vector<sf::Sound> dataSound;
};
