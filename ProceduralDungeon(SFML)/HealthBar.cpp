#include "HealthBar.h"



HealthBar::HealthBar(Player * player, ResourceManager & rm, float windowWidth, float windowHeight)
{
	this->player = player;
	sprite_iterator = rm.loadSprite("images/heart.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	offsetX = windowWidth /2 - COMMON_SPRITE_SIZE;
	offsetY = windowHeight /2 - COMMON_SPRITE_SIZE;
	hearts = player->getTries();
}

void HealthBar::draw(sf::RenderWindow & win)
{
	for (int i = 0; i < hearts; i++)
	{
		(*sprite_iterator).second.setPosition(x - (COMMON_SPRITE_SIZE * i), y);
		win.draw((*sprite_iterator).second);
	}
}
void HealthBar::update(int newX, int newY)
{
	x = newX + offsetX;
	y = newY + offsetY;
	hearts = player->getTries();
}
HealthBar::~HealthBar()
{
}
