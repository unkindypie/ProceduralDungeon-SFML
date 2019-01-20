#include "GameInterface.h"



GameInterface::GameInterface(ResourceManager & rm, GameCamera & cam, float windowHeight, float windowWidth, int quantityOfHearts)
{
	healthbar = rm.loadSprite("images/heart.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	x = cam.getX() + windowWidth / 2 - COMMON_SPRITE_SIZE;
	y = cam.getY() + windowHeight / 2 - COMMON_SPRITE_SIZE;
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	this->quantityOfHearts = quantityOfHearts;
}

void GameInterface::draw(sf::RenderWindow & win)
{

	for(int i = 0; i < quantityOfHearts; i++)
	{
		(*healthbar).second.setPosition(x - (COMMON_SPRITE_SIZE * i), y);
		win.draw((*healthbar).second);
	}
}

void GameInterface::update(GameCamera & cam, int quantityOfHearts)
{
	x = cam.getX() + windowWidth / 2 - COMMON_SPRITE_SIZE;
	y = cam.getY() + windowHeight / 2 - COMMON_SPRITE_SIZE;
	this->quantityOfHearts = quantityOfHearts;
}

GameInterface::~GameInterface()
{
}
