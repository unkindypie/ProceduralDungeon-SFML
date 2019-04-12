#pragma once
#include "ResourceManager.h"
class InterfaceObject
{
protected:
	float x, y; //координаты на экране, по которым будет проходить отрисовка
	float offsetX, offsetY; //отступ от начальных координат экрана(при смене камеры начальные координаты будут меняться)
	map<string, sf::Sprite>::iterator sprite_iterator;
	float windowHeight, windowWidth;
	bool visible = true;
public:
	InterfaceObject();
	virtual void draw(sf::RenderTarget & win) = 0;
	virtual void update(int newX, int newY) = 0;

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);

	float getOffsetX();
	float getOffsetY();
	void setOffsetX(float x);
	void setOffsetY(float y);

	bool isVisible();
	virtual void setVisibility(bool value);
	~InterfaceObject();
};

