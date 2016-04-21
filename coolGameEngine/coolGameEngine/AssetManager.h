#pragma once
#include <string>
#include <vector>

#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

class BaseState;

class AssetManager
{
public:
	AssetManager();
	//Destructor. Deletes the images and sounds.
	~AssetManager(); 

	//Return the proper data.
	sf::Image* getImage(int);
	sf::Image* getImage(std::string);
	sf::Sound* getSound(int);
	sf::SoundBuffer* getSoundBuffer(int);
	sf::SoundBuffer* getSoundBuffer(std::string);
	sf::Texture* getTexture(int);
	sf::Texture* getTexture(std::string);
	sf::Font* getFont(int);
	sf::Font* getFont(std::string);

	//Adds the proper data.
	void add(sf::Image*); 
	void add(sf::Sound*); 
	void add(sf::Texture*);
	void add(sf::SoundBuffer*);
	void add(sf::Font*);
	void addBufferString(std::string);
	void addImageString(std::string);
	void addSoundString(std::string);
	void addTextureString(std::string);
	void addFontString(std::string);

	//Clears sounds
	void clearSounds();

private:
	//Holds the data.
	std::vector<sf::Image*> image;
	std::vector<sf::Sound*> sound;
	std::vector<sf::SoundBuffer*> soundBuffer;
	std::vector<sf::Texture*> texture;
	std::vector<sf::Font*> font;
	//Holds strings in the same position as the data.
	std::vector<std::string> imageNames;
	std::vector<std::string> soundNames;
	std::vector<std::string> soundBufferNames;
	std::vector<std::string> textureNames;
	std::vector<std::string> fontNames;

};
