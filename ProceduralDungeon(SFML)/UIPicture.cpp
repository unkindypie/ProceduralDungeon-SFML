#include "UIPicture.h"



UIPicture::UIPicture(string path, ResourceManager rm, float offsetX, float offsetY, int imageWidth, int imageHeight)
{
	this->sprite_iterator = rm.loadSprite(path, sf::IntRect(0, 0, imageWidth, imageHeight));
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	visible = true;
}

void UIPicture::draw(sf::RenderWindow & win)
{
	if(visible)
	{
		int tratata = false;
		(*sprite_iterator).second.setPosition(x, y);
		win.draw( (*sprite_iterator).second);
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
