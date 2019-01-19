#pragma once
//#include "Entity.h"
#include "Bullet.h"

class Guntrap :
	public Entity
{
private:
	float currentTimeBeforeShooting;
	float shootingCooldown;
	ResourceManager & rm;
	direction dir;
public:
	Guntrap(float x, float y, ResourceManager & rm, direction dir, Sublevel * current_sublevel);
	void update(float elapsedTime);
	void draw(sf::RenderWindow & win);
	void shoot(float elapsedTime);
	~Guntrap();
};

