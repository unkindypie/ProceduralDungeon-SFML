#pragma once
#include "ResourceManager.h"

enum direction //перечисление позиций отверсти€ в подуровне
{
	left_, right_, top, down, left_top_angle, left_bottom_angle, right_top_angle, right_bottom_angle
};
class Content
{
protected:
	float x;//глобальные координаты в масштабах уровн€
	float y;
	map<string, sf::Sprite>::iterator sprite_iterator;
	sf::FloatRect rect; //пр€моугольник спрайта. — помощью него осуществл€етс€ проверка столкновений благодар€ методу intersects 
	
	bool collides;
	bool hitable;
public:

	Content();
    virtual void draw(sf::RenderWindow & win) = 0;
	virtual void update(float elapsedTime) = 0;
	bool isCollides();
	bool isHitable();
	virtual void updateRect(); //метод дл€ обновлени€ координат пр€моугольника спрайта
	sf::FloatRect getRect();
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	float & getXDirectly();
	float & getYDirectly();
	~Content();
};

