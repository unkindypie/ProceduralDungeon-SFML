#pragma once
#include "UIText.h"
class UIDebugInfo :
	public InterfaceObject
{
	UIText entitiesRendered;
	UIText entitiesUpdated;
public:
	UIDebugInfo(map<string, sf::Font>::iterator font_iterator);
	void draw(sf::RenderWindow & win);
	void update(int newX, int newY);
	virtual void setVisibility(bool value);
	~UIDebugInfo();
};

