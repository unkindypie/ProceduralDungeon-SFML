#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iterator>
#include "DebugInformation.h"
#include "GlobalValues.h"

using namespace std;


const size_t COMMON_SPRITE_SIZE = 32;
class ResourceManager
{
private:
	map<string, sf::Texture> textures; 
	map<string, sf::Sprite> sprites;
	map<string, sf::Font> fonts;
	map<string, sf::Shader*> shaders;
	void loadTexture(string path);
public:
	ResourceManager();
	map<string, sf::Sprite>::iterator loadSprite(string path, sf::IntRect rect); //загрузка спрайта, вовзращает итератор на спрайт в ассоциативном массиве, если его нет, то создает новый
	map<string, sf::Font>::iterator loadFont(string path); //загрузка шрифта
	map<string, sf::Shader*>::iterator loadShader(string name); //загрузить шейдер по названию(без пути и типа файла. функция сама подгрузит vert и frag, добавив их в путь)
	~ResourceManager();
};

