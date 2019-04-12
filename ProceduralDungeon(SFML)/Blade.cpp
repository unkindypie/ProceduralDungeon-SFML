#include "Blade.h"



Blade::Blade(float x, float y, Sublevel * sub, ResourceManager & rm, int dirX, int dirY)
{
	this->x = x;
	this->y = y;
	speed = 0.3 * speedMultiplier;
	health = 20;
	damage = 1;
	independent = true; //лезвие самостоятельное. При выходе за пределы экрана оно продолжит жить
	this->dirX = dirX;
	this->dirY = dirY;
	sprite_iterator = rm.loadSprite("images/razer.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	current_sublevel = sub;
	(*sprite_iterator).second.setOrigin(pxSizeX / 2, pxSizeY / 2);
	updateRect();
}
void Blade::update()
{
	currentRotation += speed*4;
	if(currentRotation > 360)
	{
		currentRotation = 0;
	}
	(*sprite_iterator).second.setRotation(currentRotation);
	reflect();
}
void Blade::reflect()
{
	bool collide = 0;
	x += dirX * speed;
	y += dirY * speed;
	updateRect();
	damageDealing();
	if (x - COMMON_SPRITE_SIZE / 2 - current_sublevel->getX() * COMMON_SPRITE_SIZE + dirX * speed < 0 && x + COMMON_SPRITE_SIZE / 2 - current_sublevel->getX() * COMMON_SPRITE_SIZE + dirX * speed > current_sublevel->getWidth() * COMMON_SPRITE_SIZE &&
		y - COMMON_SPRITE_SIZE / 2 - current_sublevel->getY() * COMMON_SPRITE_SIZE + dirY * speed < 0 && y + COMMON_SPRITE_SIZE / 2 - current_sublevel->getY() * COMMON_SPRITE_SIZE + dirY * speed > current_sublevel->getHeight() * COMMON_SPRITE_SIZE)
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
		x -= dirX * speed * 7;
		y -= dirY * speed * 7;
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
void Blade::draw(sf::RenderTarget & win)
{
	sprite_iterator->second.setPosition(x, y);
	win.draw(sprite_iterator->second);
}
Blade::~Blade()
{
}
