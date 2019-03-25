#include "GameInterface.h"
#include <sstream>;
//#include "Entity.h"
#include "Player.h"
#include "HealthBar.h"
#include "UIPicture.h"

GameInterface::GameInterface(ResourceManager & rm, GameCamera & cam, float windowHeight, float windowWidth, int quantityOfHearts)
{
	/*healthbar = rm.loadSprite("images/heart.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	gameOver = rm.loadSprite("images/gameover.png", sf::IntRect(0, 0, 304, 200));
	(*gameOver).second.setOrigin(304 / 2, 200 / 2);
	gamePassed = rm.loadSprite("images/gamepassed.png", sf::IntRect(0, 0, 200, 310));
	(*gamePassed).second.setOrigin(200 / 2, 310 / 2);
	x = cam.getX() + windowWidth / 2 - COMMON_SPRITE_SIZE;
	y = cam.getY() + windowHeight / 2 - COMMON_SPRITE_SIZE;
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	this->quantityOfHearts = quantityOfHearts;

	ostringstream ss;
	ss << dynamic_cast<Entity*>(cam.getTarget())->getSpeed();
	playerSpeed = ss.str();*/
}
GameInterface::GameInterface(Level * level, float windowHeight, float windowWidth, GameCamera & cam) 
{
	objects.push_back(new HealthBar(dynamic_cast<Player*>(level->player), level->getResourceManager(), windowWidth, windowHeight));
	objects.push_back(new UIPicture("images/gameover.png", 0, 0, level->getResourceManager().loadSprite("images/gameover.png", sf::IntRect(0, 0, 304, 200))));
	objects.push_back(new UIPicture("images/gamepassed.png", 0,0, level->getResourceManager().loadSprite("images/gamepassed.png", sf::IntRect(0, 0, 200, 310))));
	objects[1]->setVisibility(false);
	objects[2]->setVisibility(false);
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
	x = cam.getX();
	y = cam.getY();
}
void GameInterface::draw(sf::RenderWindow & win)
{
	if(isGameOver)
	{
		objects[1]->setVisibility(true);
	}
	else if(isGamePassed)
	{
		objects[2]->setVisibility(true);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->draw(win);
	}
		


	/*	for (int i = 0; i < quantityOfHearts; i++)
		{
			(*healthbar).second.setPosition(x - (COMMON_SPRITE_SIZE * i), y);
			win.draw((*healthbar).second);
		}
		sf::Text txt;
		sf::Font font;
		font.loadFromFile("fonts/prstart.ttf");
		txt.setFont(font);
		txt.setString(playerSpeed);
		txt.setPosition(x - 200, y - 100);
		win.draw(txt);*/

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
	ostringstream ss;
	ss << dynamic_cast<Entity*>(cam.getTarget())->getSpeed();
	playerSpeed = ss.str();
}

void GameInterface::update(float x, float y)
{
	this->x = x;
	this->y = y;
	for(int i = 0; i < objects.size(); i++)
	{
		objects[i]->update(x, y);
	}
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
