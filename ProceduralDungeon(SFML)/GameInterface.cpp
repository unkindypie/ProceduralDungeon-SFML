#include "GameInterface.h"
//#include "Entity.h"
#include "Player.h"
#include "HealthBar.h"
#include "UIPicture.h"
#include "FPSMonitor.h"
#include "UIDebugInfo.h"
#include <iostream>

GameInterface::GameInterface(Level * level, GameCamera & cam) 
{
	this->windowHeight = GlobalValues::getViewHeight();
	this->windowWidth = GlobalValues::getViewWidth();
	x = cam.getX();
	y = cam.getY();
	
	std::cout << windowHeight << endl;

	objects.push_back(new HealthBar(dynamic_cast<Player*>(level->player), level->getResourceManager(), this->windowWidth, this->windowHeight));
	objects.push_back(new UIPicture("images/gameover.png", 0, 0, level->getResourceManager().loadSprite("images/gameover.png", sf::IntRect(0, 0, 304, 200))));
	objects.push_back(new UIPicture("images/gamepassed.png", 0,0, level->getResourceManager().loadSprite("images/gamepassed.png", sf::IntRect(0, 0, 200, 310))));
	objects[1]->setVisibility(false);
	objects[2]->setVisibility(false);
	objects.push_back(new FPSMonitor(level->getResourceManager().loadFont("fonts/prstart.ttf")));
	objects.push_back(new UIDebugInfo(level->getResourceManager().loadFont("fonts/prstart.ttf")));
}
void GameInterface::draw(sf::RenderTarget & win)
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
