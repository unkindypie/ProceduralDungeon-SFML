#include "Guntrap.h"




Guntrap::Guntrap(float x, float y, ResourceManager & rm1, direction dir, Sublevel * current_sublevel) : rm(rm1)
{
	sprite_iterator = rm.loadSprite("images/guntrap.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	shootingCooldown = 50;
	currentTimeBeforeShooting = 0;
	independent = true; //������� ���������������. ��� ������ �� ������� ������ ��� ��������� ����.
	this->x = x;
	this->y = y;
	(*sprite_iterator).second.setPosition(x, y);
	this->dir = dir;
	this->current_sublevel = current_sublevel;
	switch (dir)
	{
	case left_:
		(*sprite_iterator).second.setRotation(-90);
		break;
	case right_:
		(*sprite_iterator).second.setRotation(90);
		break;
	case top:
		(*sprite_iterator).second.setRotation(0);
		break;
	case down:
		(*sprite_iterator).second.setRotation(180);
		break;
	default:
		break;
	}
	updateRect();
}
void Guntrap::update()
{
	currentTimeBeforeShooting += 1;
	if(currentTimeBeforeShooting >= shootingCooldown)
	{
		shoot();
		currentTimeBeforeShooting = 0;
	}
	//if(shootingClock.getElapsedTime().asMilliseconds() >= 2000)
	//{
	//	shoot();
	//	shootingClock.restart();
	//}
}
void Guntrap::shoot()
{
	switch (dir)
	{
	case left_:
		current_sublevel->addEntity(new Bullet(x + COMMON_SPRITE_SIZE, y - COMMON_SPRITE_SIZE / 2, 1, 0, current_sublevel, rm));
		break;
	case right_:
		current_sublevel->addEntity(new Bullet(x - COMMON_SPRITE_SIZE, y + COMMON_SPRITE_SIZE / 2, -1, 0, current_sublevel, rm));
		break;
	case top:
		current_sublevel->addEntity(new Bullet(x + COMMON_SPRITE_SIZE/2, y + COMMON_SPRITE_SIZE, 0, 1, current_sublevel, rm));
		break;
	case down:
		current_sublevel->addEntity(new Bullet(x - COMMON_SPRITE_SIZE / 2, y - COMMON_SPRITE_SIZE, 0, -1, current_sublevel, rm));
		break;
	default:
		break;
	}
}
void Guntrap::draw(sf::RenderTarget & win)
{
	switch (dir)
	{
	case left_:
		(*sprite_iterator).second.setRotation(-90);
		break;
	case right_:
		(*sprite_iterator).second.setRotation(90);
		break;
	case top:
		(*sprite_iterator).second.setRotation(0);
		break;
	case down:
		(*sprite_iterator).second.setRotation(180);
		break;
	default:
		break;
	}
	sprite_iterator->second.setPosition(x, y);
	win.draw(sprite_iterator->second);
}
Guntrap::~Guntrap()
{
}
