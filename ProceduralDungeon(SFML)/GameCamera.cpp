#include "GameCamera.h"
#include "GlobalValues.h"


GameCamera::GameCamera(Content * target, sf::RenderTarget & win) : win(win)
{
	this->target = target;
	speed = 4.3;
	x = win.getSize().x / 2;
	y = win.getSize().y / 2;
	view.reset(sf::FloatRect(x, y, win.getSize().x, win.getSize().y));
}
void GameCamera::update(float elapasedTime)
{
	view.setCenter(target->getX(), target->getY());
	x = target->getX();
	y = target->getY();
	inputConroledMove();

	if(x < target->getX())
	{
		move(target->getX(), y);
	}
	if (x > target->getX())
	{
		move(target->getX(), y);
	}
	if (y < target->getY())
	{
		move(x, target->getY());
	}
	if (y > target->getY())
	{
		move(x, target->getY());
	}
	view.setCenter(x, y);
	win.setView(view);
}
void GameCamera::move(float x, float y)
{
	if(this->x < x)
	{
		this->x +=  0.5 * speed;
	}
	if (this->x > x)
	{
		this->x -=  0.5 * speed;
	}
	if (this->y < y)
	{
		this->y += 0.5 * speed;
	}
	
}
void GameCamera::inputConroledMove()
{
	size_t offset = 3;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		y -= offset;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		y += offset;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		x += offset;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		x -= offset;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		GlobalValues::zoomScaleFactor = 0.5;
		view.setSize(GlobalValues::getWindowWidth() * GlobalValues::zoomScaleFactor, GlobalValues::getWindowHeight() * GlobalValues::zoomScaleFactor);
		GlobalValues::setViewWidth(GlobalValues::getWindowWidth() / 2);
		GlobalValues::setViewHeight(GlobalValues::getWindowHeight() / 2);
	}
	view.setCenter(x, y);
}
void GameCamera::deathcam()//красиво пролетаю по уровню под конец
{
	speed *= 1.1;
	target->setY(8000);
}
float GameCamera::getX()
{
	return x;
}
float GameCamera::getY()
{
	return y;
}
Content * GameCamera::getTarget()
{
	return target;
}
GameCamera::~GameCamera()
{
}
