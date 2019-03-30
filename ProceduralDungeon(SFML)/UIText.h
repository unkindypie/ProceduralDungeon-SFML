#pragma once
#include "InterfaceObject.h"
class UIText :
	public InterfaceObject
{
public:
	sf::Text text;
	UIText();
	UIText(string str, map<string, sf::Font>::iterator font_iterator, float offsetX, float offsetY);
	void draw(sf::RenderWindow & win);
	virtual void update(int newX, int newY);
	~UIText();
};

