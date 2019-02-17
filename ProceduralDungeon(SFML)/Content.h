#pragma once
#include "ResourceManager.h"
const size_t COMMON_SPRITE_SIZE = 32;
enum direction //перечисление позиций отверстия в подуровне
{
	left_, right_, top, down, left_top_angle, left_bottom_angle, right_top_angle, right_bottom_angle
};
class Content
{
protected:
	float x;//глобальные координаты в масштабах уровня
	float y;
	//sf::Sprite * sprite = nullptr; //указатель на спрайт, который лежит в словаре в классе ResourceManager
	map<string, sf::Sprite>::iterator sprite_iterator;
	sf::FloatRect rect; //прямоугольник спрайта. С помощью него осуществляется проверка столкновений благодаря методу intersects 
	
	bool collides;
	bool hitable;
public:

	Content();
    virtual void draw(sf::RenderWindow & win) = 0;
	virtual void update(float elapsedTime) = 0;
	bool isCollides();
	bool isHitable();
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

