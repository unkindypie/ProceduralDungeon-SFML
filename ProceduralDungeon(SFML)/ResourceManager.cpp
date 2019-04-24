#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}
void ResourceManager::loadTexture(string path)
{
	if(textures.find(path) == textures.end()) //в случае, если такой текстурки нет, то добавл€ю ее
	{
		sf::Texture texture;
		texture.loadFromFile(path);
		texture.setRepeated(true);
		textures.emplace(path, texture);
	}
}
map<string, sf::Sprite>::iterator ResourceManager::loadSprite(string path, sf::IntRect rect)
{
	if (sprites.find(path) == sprites.end()) //если такого спрайта нет, то добавл€ю его
	{
		loadTexture(path); 
		sprites.emplace(path, sf::Sprite(textures.find(path)->second));
		sprites[path].setTextureRect(rect);
		sprites[path].setPosition(0, 0);
	}
	return sprites.find(path); //возвращаю указатель на этот спрайт

}
map<string, sf::Sprite>::iterator ResourceManager::downloadSprite(string path, sf::Sprite sprite)
{
	if (sprites.find(path) == sprites.end()) //если такого спрайта нет, то добавл€ю его
	{
		sprites.emplace(path, sprite);
	}
	return sprites.find(path);
}
map<string, sf::Font>::iterator ResourceManager::loadFont(string path)
{
	if(fonts.find(path) == fonts.end())//если шрифта нет в асоциативном массиве - добавл€ю
	{
		sf::Font newfont;
		newfont.loadFromFile(path);
		fonts.emplace(path, newfont);
	}
	return fonts.find(path);
}
map<string, sf::Shader*>::iterator ResourceManager::loadShader(string name)
{
	if(shaders.find(name) == shaders.end())
	{
		sf::Shader shader;
		shader.loadFromFile("shaders/" + name + ".vert", "shaders/" + name + ".frag");
		shaders.emplace(name, &shader);
	}
	return shaders.find(name);
}
ResourceManager::~ResourceManager()
{
}
