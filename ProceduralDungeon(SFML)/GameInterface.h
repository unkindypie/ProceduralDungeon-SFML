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
	int quantityOfHearts;
	map<string, sf::Sprite>::iterator healthbar;
	map<string, sf::Sprite>::iterator gameOver;
	map<string, sf::Sprite>::iterator gamePassed;
	string playerSpeed;



	vector<InterfaceObject*> objects;
	

public:
	GameInterface(ResourceManager & rm, GameCamera & cam, float windowHeight, float windowWidth, int quantityOfHearts);
	GameInterface(Level * level, float windowHeight, float windowWidth, GameCamera & cam);

	void draw(sf::RenderWindow & win);
	void update(GameCamera & cam, int quantityOfHearts);
	void update(float x, float y);
	void gameover();
	void gamepassed();
	~GameInterface();
};

