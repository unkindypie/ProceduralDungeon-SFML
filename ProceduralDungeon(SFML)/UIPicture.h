#pragma once
#include "InterfaceObject.h"
class UIPicture :
	public InterfaceObject
{
public:
	UIPicture();
	UIPicture(string path, float offsetX, float offsetY, map<string, sf::Sprite>::iterator sprite_iterator);
	void draw(sf::RenderWindow & win);
	void update(int newX, int newY);
	~UIPicture();
};

