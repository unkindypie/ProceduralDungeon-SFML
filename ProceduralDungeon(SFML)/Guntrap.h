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
	static sf::Clock shootingClock;
public:
	Guntrap(float x, float y, ResourceManager & rm, direction dir, Sublevel * current_sublevel);
	void update();
	void draw(sf::RenderTarget & win);
	void shoot();
	~Guntrap();
};
sf::Clock Guntrap::shootingClock;
