#pragma once
//#include "Block.cpp"
#include "Block.h"
#include "Sublevel.h"
#include "AnimationManager.h"
//#include "Level.h"


//enum EntityType
//{
//	invisible, cross, snake, v_arrow_up, v_arrow_down, v_arrow_right, v_arrow_left 
//};

class Entity : public Content //класс сущность. Представляет собой объект с возможностью движения по подуровню, смены подуровня, получения и нанесения урона
{
protected:
	float health;
	float damage;
	double speed;
	Sublevel * current_sublevel;
	AnimationManager am;
public:
	void move(float dirX, float dirY, float elapsedTime); //метод передвижения по уровню с проверкой столкновений
	void updateRect(); //метод для обновления координат прямоугольника спрайта
	void hit(Entity * en); //нанесение урона
	virtual void decreaseHealth(float value); //метод уменьшения здоровья этой сущности на конкретное значение(виртуальный, поскольку перегружен для игрока)
	bool damageDealing(); //метод проверки и вслучае успеха нанесения урона. Если столкновений с объектом, которого можно ударить не обнаружено, то вернет false
	Entity();
	~Entity();
};

