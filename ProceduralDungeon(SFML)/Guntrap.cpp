#include "Guntrap.h"




Guntrap::Guntrap(float x, float y, ResourceManager & rm1, direction dir, Sublevel * current_sublevel) : rm(rm1)
{
	sprite_iterator = rm.loadSprite("images/guntrap.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	shootingCooldown = 12;
	currentTimeBeforeShooting = 0;
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
}
void Guntrap::update(float elapsedTime)
{
	currentTimeBeforeShooting += elapsedTime;
	if(currentTimeBeforeShooting >= shootingCooldown)
	{
		shoot(elapsedTime);
		currentTimeBeforeShooting = 0;
	}
}
void Guntrap::shoot(float elapsedTime)
{
	switch (dir)
	{
	case left_:
		current_sublevel->addContent(new Bullet(x + COMMON_SPRITE_SIZE, y - COMMON_SPRITE_SIZE / 2, 1, 0, current_sublevel, rm));
		break;
	case right_:
		current_sublevel->addContent(new Bullet(x - COMMON_SPRITE_SIZE, y + COMMON_SPRITE_SIZE / 2, -1, 0, current_sublevel, rm));
		break;
	case top:
		current_sublevel->addContent(new Bullet(x + COMMON_SPRITE_SIZE/2, y + COMMON_SPRITE_SIZE, 0, 1, current_sublevel, rm));
		break;
	case down:
		current_sublevel->addContent(new Bullet(x - COMMON_SPRITE_SIZE / 2, y - COMMON_SPRITE_SIZE, 0, -1, current_sublevel, rm));
		break;
	default:
		break;
	}
}
void Guntrap::draw(sf::RenderWindow & win)
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
