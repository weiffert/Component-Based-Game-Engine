#pragma once

#include <string>
#include <vector>

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "Entity.h"


class BaseComponent 
{
public:
	BaseComponent();
	~BaseComponent();

	//Edit id.
	std::string getId();
	void setId(std::string);

	//Returns the data as a vector.
	/*
	virtual std::vector<int> getData() = 0;
	virtual int getData(int) = 0;

	virtual std::vector<double> getData() = 0;
	virtual double getData(int) = 0;

	virtual std::vector<float> getData() = 0;
	virtual float getData(int) = 0;

	virtual std::vector<char> getData() = 0;
	virtual char getData(int) = 0;

	virtual std::vector<bool> getData() = 0;
	virtual bool getData(int) = 0;

	virtual std::vector<sf::Image> getData() = 0;
	virtual sf::Image getData(int) = 0;

	virtual std::vector<sf::Sound> getData() = 0;
	virtual sf::Sound getData(int) = 0;

	virtual std::vector<sf:Texture> getData() = 0;
	virtual sf::Texture getData(int) = 0;

	virtual std::vector<sf::Sprite> getData() = 0;
	virtual sf::Sprite getData(int) = 0;

	virtual std::vector<sf::Shape> getData() = 0;
	virtual sf::Shape getData(int) = 0;

	virtual std::vector<sf::Text> getData() = 0;
	virtual sf::Text getData(int) = 0;

	virtual std::vector<Entity> getData() = 0;
	virtual Entity getData(int) = 0;
	*/
	template<class T>
	virtual std::vector<T> getData() = 0;
	template<class T>
	virtual T getData(int) = 0;

	//Edit the data.
	virtual void deleteDataPosition(int) = 0;
	virtual void deleteData() = 0;

	virtual void addData(int) = 0;
	virtual void deleteData(int) = 0;
	virtual void changeData(int, int) = 0;

	virtual void addData(double) = 0;
	virtual void deleteData(double) = 0;
	virtual void changeData(double, int) = 0;

	virtual void addData(float) = 0;
	virtual void deleteData(float) = 0;
	virtual void changeData(float, int) = 0;

	virtual void addData(char) = 0;
	virtual void deleteData(char) = 0;
	virtual void changeData(char, int) = 0;

	virtual void addData(bool) = 0;
	virtual void deleteData(bool) = 0;
	virtual void changeData(bool, int) = 0;

	virtual void addData(sf::Image) = 0;
	virtual void deleteData(sf::Image) = 0;
	virtual void changeData(sf::Image, int) = 0;

	virtual void addData(sf::Texture) = 0;
	virtual void deleteData(sf::Texture) = 0;
	virtual void changeData(sf::Texture, int) = 0;

	virtual void addData(sf::Sound) = 0;
	virtual void deleteData(sf::Sound) = 0;
	virtual void changeData(sf::Sound, int) = 0;

	virtual void addData(sf::Sprite) = 0;
	virtual void deleteData(sf::Sprite) = 0;
	virtual void changeData(sf::Sprite, int) = 0;

	virtual void addData(sf::Shape) = 0;
	virtual void deleteData(sf::Shape) = 0;
	virtual void changeData(sf::Shape, int) = 0;

	virtual void addData(sf::Text) = 0;
	virtual void deleteData(sf::Text) = 0;
	virtual void changeData(sf::Text, int) = 0;

	virtual void addData(Entity) = 0;
	virtual void deleteData(Entity) = 0;
	virtual void changeData(Entity, int) = 0;

protected:
	std::string id;
};

