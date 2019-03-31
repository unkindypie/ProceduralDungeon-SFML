#pragma once
#include "ResourceManager.h"

enum direction //перечисление позиций отверстия в подуровне
{
	left_, right_, top, down, left_top_angle, left_bottom_angle, right_top_angle, right_bottom_angle
};
class Content
{
protected:
	float x;//глобальные координаты в масштабах уровня
	float y;
	map<string, sf::Sprite>::iterator sprite_iterator;
	sf::FloatRect rect; //прямоугольник спрайта. С помощью него осуществляется проверка столкновений благодаря методу intersects 
	
	bool collides; //иммет ли объект коллизии
	bool hitable; //можно ли его ударить
	bool independent; //умрет ли он при выходе за границы экрана или продолжит жить
public:

	Content();
    virtual void draw(sf::RenderWindow & win) = 0;
	virtual void update() = 0;
	bool isCollides();
	bool isHitable();
	bool isIndependent();
	virtual void updateRect(); //метод для обновления координат прямоугольника спрайта
	sf::FloatRect getRect();
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	float & getXDirectly();
	float & getYDirectly();
	~Content();
};

