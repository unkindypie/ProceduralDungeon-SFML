#pragma once
#include "InterfaceObject.h"
class UIPicture :
	public InterfaceObject
{
public:
	UIPicture(string path, ResourceManager rm, float offsetX, float offsetY, int imageWidth, int imageHeight);
	void draw(sf::RenderWindow & win);
	void update(int newX, int newY);
	~UIPicture();
};

