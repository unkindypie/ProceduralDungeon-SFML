#include "Content.h"



Content::Content()
{
}
bool Content::isCollides()
{
	return collides;
}
bool Content::isHitable()
{
	return hitable;
}
float Content::getX()
{
	return x;
}
float Content::getY()
{
	return y;
}

void Content::setX(float x)
{
	this->x = x;
}
void Content::setY(float y)
{
	this->y = y;
}
float & Content::getXDirectly()
{
	return x;
}
float & Content::getYDirectly()
{
	return y;
}
sf::FloatRect Content::getRect()
{
	return rect;
}
void Content::updateRect()
{
	(*sprite_iterator).second.setPosition(x, y);
	rect = (*sprite_iterator).second.getGlobalBounds();
}
Content::~Content()
{
}
