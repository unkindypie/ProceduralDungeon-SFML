#pragma once
#include "GameCamera.h"
class GameInterface
{
	float windowHeight;
	float windowWidth;
	float x;
	float y;
	int quantityOfHearts;
	map<string, sf::Sprite>::iterator healthbar;
public:
	GameInterface(ResourceManager & rm, GameCamera & cam, float windowHeight, float windowWidth, int quantityOfHearts);
	void draw(sf::RenderWindow & win);
	void update(GameCamera & cam, int quantityOfHearts);
	~GameInterface();
};

