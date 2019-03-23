#pragma once
#include "InterfaceObject.h"
#include "Player.h"

class HealthBar :
	public InterfaceObject
{
protected:
	int hearts;
	Player * player;
public:
	HealthBar(Player * player, ResourceManager & rm, float windowWidth, float windowHeight);
	void draw(sf::RenderWindow & win);
	void update(int newX, int newY);
	~HealthBar();
};
