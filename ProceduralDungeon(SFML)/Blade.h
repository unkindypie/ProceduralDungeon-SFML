#pragma once
#include "Entity.h"
class Blade :
	public Entity
{
private:
	int dirX = 0;
	int dirY = -1;
	int currentRotation = 0;
public:
	Blade(float x, float y, Sublevel * sub, ResourceManager & rm, int dirX, int dirY);
	void update(float elapsedTime);
	void draw(sf::RenderWindow & win);
	void reflect(float elapsedTime);
	~Blade();
};

