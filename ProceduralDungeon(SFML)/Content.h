#pragma once
#include "ResourceManager.h"
const size_t COMMON_SPRITE_SIZE = 16;
class Content
{
protected:
	float x;//глобальные координаты в масштабах уровн€
	float y;
	//sf::Sprite * sprite = nullptr; //указатель на спрайт, который лежит в словаре в классе ResourceManager
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

