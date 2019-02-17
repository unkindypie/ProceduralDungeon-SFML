#pragma once
//#include "Block.cpp"
#include "Block.h"
#include "Sublevel.h"
#include "AnimationManager.h"
//#include "Level.h"

class Entity : public Content //класс сущность. Представляет собой объект с возможностью движения по подуровню, смены подуровня, получения и нанесения урона
{
protected:
	float health;
	float damage;
	double speed;
	static float speedMultiplier;
	Sublevel * current_sublevel;
	AnimationManager am;
public:
	size_t pxSizeX = 16;
	size_t pxSizeY = 16;
	void move(float dirX, float dirY, float elapsedTime); //метод передвижения по уровню с проверкой столкновений
	void updateRect(); //метод для обновления координат прямоугольника спрайта
	void hit(Entity * en); //нанесение урона
	bool isDirectedToHole(float dirX, float dirY, holeMode hole);
	Sublevel * getCurrentSublevel();
	double getSpeed();
	virtual void decreaseHealth(float value); //метод уменьшения здоровья этой сущности на конкретное значение(виртуальный, поскольку перегружен для игрока)
	bool damageDealing(); //метод проверки и вслучае успеха нанесения урона. Если столкновений с объектом, которого можно ударить не обнаружено, то вернет false
	Entity();
	~Entity();
};
float Entity::speedMultiplier = 10;
