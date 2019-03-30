#include "UIText.h"


UIText::UIText()
{
}

UIText::UIText(string str, map<string, sf::Font>::iterator font_iterator, float offsetX, float offsetY)
{
	text.setFont((*font_iterator).second);
	text.setString(str);
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}
void UIText::draw(sf::RenderWindow & win)
{
	if(visible)
	{
		text.setPosition(x, y);
		win.draw(text);
	}
}

void UIText::update(int newX, int newY)
{
	x = newX + offsetX;
	y = newY + offsetY;
}

UIText::~UIText()
{
}
