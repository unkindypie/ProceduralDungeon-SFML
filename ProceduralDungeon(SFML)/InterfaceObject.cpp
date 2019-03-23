#include "InterfaceObject.h"



InterfaceObject::InterfaceObject()
{
}
float InterfaceObject::getX()
{
	return x;
}
float InterfaceObject::getY()
{
	return y;
}

void InterfaceObject::setX(float x)
{
	this->x = x;
}
void InterfaceObject::setY(float y)
{
	this->y = y;
}
float InterfaceObject::getOffsetX()
{
	return offsetX;
}
float InterfaceObject::getOffsetY()
{
	return offsetY;
}

void InterfaceObject::setOffsetX(float offsetX)
{
	this->offsetX = offsetX;
}
void InterfaceObject::setOffsetY(float offsetY)
{
	this->offsetY = offsetY;
}
bool InterfaceObject::isVisible()
{
	return visible;
}
void InterfaceObject::setVisibility(bool value)
{
	visible = value;
}

InterfaceObject::~InterfaceObject()
{
}
