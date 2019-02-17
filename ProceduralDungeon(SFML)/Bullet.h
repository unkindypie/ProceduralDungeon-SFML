#pragma once
#include "Entity.h"
class Bullet :
	public Entity
{
protected:
	int dirX, dirY;
public:
	size_t pxSizeX = 16;
	size_t pxSizeY = 16;
	Bullet();
	Bullet(float x, float y, int dirX, int dirY, Sublevel * current_sublevel, ResourceManager & rm);
	void hitDetection(float elapsedTime);
	void update(float elapsedTime);
	void draw(sf::RenderWindow & win);
	void fly(float elapsedTime);
	~Bullet();
};

