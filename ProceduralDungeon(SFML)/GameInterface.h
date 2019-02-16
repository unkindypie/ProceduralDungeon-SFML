#pragma once
#include "GameCamera.h"
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
public:
	GameInterface(ResourceManager & rm, GameCamera & cam, float windowHeight, float windowWidth, int quantityOfHearts);
	void draw(sf::RenderWindow & win);
	void update(GameCamera & cam, int quantityOfHearts);
	void gameover();
	void gamepassed();
	~GameInterface();
};

