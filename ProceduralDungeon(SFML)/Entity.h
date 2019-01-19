#pragma once
//#include "Block.cpp"
#include "Block.h"
#include "Sublevel.h"
#include "AnimationManager.h"
//#include "Level.h"


enum EntityType
{
	invisible, cross, snake, v_arrow_up, v_arrow_down, v_arrow_right, v_arrow_left 
};

class Entity : public Content
{
protected:
	EntityType type;
	float health;
	float damage;
	double speed;
	Sublevel * current_sublevel;
	size_t vectorPosition;
	AnimationManager am;
public:
	void move(float dirX, float dirY, float elapsedTime); //метод передвижения по уровню с проверкой столкновений
	void setEntityType(EntityType type);
	//void collisionCheck(direction dir);
	void updateRect(); //метод для обновления координат прямоугольника спрайта
	void hit(Entity * en);
	void decreaseHealth(float value);
	EntityType getType();
	//void draw(sf::RenderWindow & win);
	Entity();
	~Entity();
};

