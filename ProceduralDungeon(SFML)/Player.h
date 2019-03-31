#pragma once
#include "Entity.h"
#include "Bullet.h"

//#include "Sublevel.h"


class Player :
	public Entity
{
protected:
	int dirX, dirY;
//	float currentTime;
//	float shootingCooldown;
	bool gameOver = 0;
	bool levelPassed = 0;
	int tries;
	ResourceManager & rm;
public:
	Player(float x, float y, Sublevel * sub, ResourceManager & rm);
	void draw(sf::RenderWindow & win);
	void movement();
	void update();
	ResourceManager & getResourceManager();
	bool isGameOver();
	bool isLevelPassed();
	void shoot();
	int getTries();
	void decreaseHealth(float value);
	~Player();
};

