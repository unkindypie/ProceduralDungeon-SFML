#include "GameInterface.h"



GameInterface::GameInterface(ResourceManager & rm, GameCamera & cam, float windowHeight, float windowWidth, int quantityOfHearts)
{
	healthbar = rm.loadSprite("images/heart.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	gameOver = rm.loadSprite("images/gameover.png", sf::IntRect(0, 0, 304, 200));
	(*gameOver).second.setOrigin(304 / 2, 200 / 2);
	gamePassed = rm.loadSprite("images/gamepassed.png", sf::IntRect(0, 0, 200, 310));
	(*gamePassed).second.setOrigin(200 / 2, 310 / 2);
	x = cam.getX() + windowWidth / 2 - COMMON_SPRITE_SIZE;
	y = cam.getY() + windowHeight / 2 - COMMON_SPRITE_SIZE;
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	this->quantityOfHearts = quantityOfHearts;
}

void GameInterface::draw(sf::RenderWindow & win)
{
	if(isGameOver)
	{
		(*gameOver).second.setPosition(x, y);
		win.draw((*gameOver).second);
	}
	else if(isGamePassed)
	{
		(*gamePassed).second.setPosition(x, y);
		win.draw((*gamePassed).second);
	}
	else
	{
		for (int i = 0; i < quantityOfHearts; i++)
		{
			(*healthbar).second.setPosition(x - (COMMON_SPRITE_SIZE * i), y);
			win.draw((*healthbar).second);
		}
	}
	
}

void GameInterface::update(GameCamera & cam, int quantityOfHearts)
{
	
	x = cam.getX() + windowWidth / 2 - COMMON_SPRITE_SIZE;
	y = cam.getY() + windowHeight / 2 - COMMON_SPRITE_SIZE;
	if(isGamePassed || isGameOver)
	{
		x = cam.getX();
		y = cam.getY();
	}
	this->quantityOfHearts = quantityOfHearts;
}

void GameInterface::gamepassed()
{
	isGamePassed = 1;
}
void GameInterface::gameover()
{
	isGameOver = 1;
}
GameInterface::~GameInterface()
{
	
}
