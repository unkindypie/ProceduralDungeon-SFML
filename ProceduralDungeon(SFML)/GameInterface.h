#pragma once
#include "GameCamera.h"
#include "InterfaceObject.h"
#include "Level.h"

class GameInterface
{
	float windowHeight;
	float windowWidth;
	float x;
	float y;
	bool isGamePassed = 0;
	bool isGameOver = 0;
	vector<InterfaceObject*> objects;
	

public:
	GameInterface(Level * level, GameCamera & cam);

	void draw(sf::RenderTarget & win);
	void update(float x, float y);
	void gameover();
	void gamepassed();
	~GameInterface();
};

