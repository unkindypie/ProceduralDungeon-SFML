#include "Blade.h"



Blade::Blade(float x, float y, Sublevel * sub, ResourceManager & rm, int dirX, int dirY)
{
	this->x = x;
	this->y = y;
	speed = 0.3;
	health = 20;
	damage = 1;
	this->dirX = dirX;
	this->dirY = dirY;
	sprite_iterator = rm.loadSprite("images/razer.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	current_sublevel = sub;
	(*sprite_iterator).second.setOrigin(COMMON_SPRITE_SIZE / 2, COMMON_SPRITE_SIZE / 2);
	updateRect();
}
void Blade::update(float elapsedTime)
{
	currentRotation += speed*4 * elapsedTime;
	if(currentRotation > 360)
	{
		currentRotation = 0;
	}
	(*sprite_iterator).second.setRotation(currentRotation);
	reflect(elapsedTime);
}
void Blade::reflect(float elapsedTime)
{
	elapsedTime *= speed;
	bool collide = 0;
	x += dirX * elapsedTime; 
	y += dirY * elapsedTime;
	updateRect();
	damageDealing();
	if (x - COMMON_SPRITE_SIZE / 2 - current_sublevel->getX() * COMMON_SPRITE_SIZE + dirX * elapsedTime < 0 && x + COMMON_SPRITE_SIZE / 2 - current_sublevel->getX() * COMMON_SPRITE_SIZE + dirX * elapsedTime > current_sublevel->getWidth() * COMMON_SPRITE_SIZE &&
		y - COMMON_SPRITE_SIZE / 2 - current_sublevel->getY() * COMMON_SPRITE_SIZE + dirY * elapsedTime < 0 && y + COMMON_SPRITE_SIZE / 2 - current_sublevel->getY() * COMMON_SPRITE_SIZE + dirY * elapsedTime > current_sublevel->getHeight() * COMMON_SPRITE_SIZE)
	{
		collide = 1;
	}
	else
	{
		for (int i = (rect.top - current_sublevel->getY()*COMMON_SPRITE_SIZE) / COMMON_SPRITE_SIZE; i < (rect.top - current_sublevel->getY()*COMMON_SPRITE_SIZE + rect.height) / COMMON_SPRITE_SIZE; i++)
		{
			for (int j = (rect.left - current_sublevel->getX()*COMMON_SPRITE_SIZE) / COMMON_SPRITE_SIZE; j < ((rect.left - current_sublevel->getX()*COMMON_SPRITE_SIZE) + rect.width) / COMMON_SPRITE_SIZE; j++)
			{
				if (current_sublevel->getMap()[i][j]->getRect().intersects(rect) && current_sublevel->getMap()[i][j]->isCollides())
				{
					collide = 1;
				}
			}
		}
	}
	
	if (collide)  
	{
		x -= dirX * elapsedTime * 7;
		y -= dirY * elapsedTime * 7;
		updateRect();
		if (dirX == 1 && dirY == -1)
		{
			dirX = 1;
			dirY = 1;
		}
		else if (dirX == 1 && dirY == 1)
		{
			dirX = -1;
			dirY = 1;
		}
		else if (dirX == -1 && dirY == 1)
		{
			dirX = -1;
			dirY = -1;
		}
		else if (dirX == -1 && dirY == -1)
		{
			dirX = 1;
			dirY = -1;
		}
	}
}
void Blade::draw(sf::RenderWindow & win)
{
	sprite_iterator->second.setPosition(x, y);
	win.draw(sprite_iterator->second);
}
Blade::~Blade()
{
}
