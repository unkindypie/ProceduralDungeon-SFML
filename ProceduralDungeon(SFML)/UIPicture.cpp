#include "UIPicture.h"


UIPicture::UIPicture(){}
UIPicture::UIPicture(string path, float offsetX, float offsetY, map<string, sf::Sprite>::iterator sprite_iterator)
{
	this->sprite_iterator = sprite_iterator;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	visible = true;
}

void UIPicture::draw(sf::RenderWindow & win)
{
	if(visible)
	{
		(*sprite_iterator).second.setPosition(x, y);
		win.draw((*sprite_iterator).second);
	}
}

void UIPicture::update(int newX, int newY)
{
	x = newX + offsetX;
	y = newY + offsetY;
}

UIPicture::~UIPicture()
{
}
