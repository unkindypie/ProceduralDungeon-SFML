#pragma once
#include "Content.h"
class GameCamera
{
	float x, y;
	float speed;
	Content * target;
	sf::RenderTarget & win;
	sf::View view;
public:

	GameCamera(Content * target, sf::RenderTarget & win);
	void move(float x, float y);
	void inputConroledMove();
	void update(float elapasedTime);
	Content * getTarget();
	float getX();
	float getY();
	void deathcam();
	~GameCamera();
};

