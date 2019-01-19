#pragma once
#include "Sublevel.h"
//#include "Entity.h"
//#include <windows.h>
const bool DEBUG_GENERATION_DRAW = false; //отрисовка подуровней во время работы конструктора уровня

//void drawSublevel(Sublevel & sublevel, sf::RenderWindow & win, float elapsedTime)
//{
//	for (int i = 0; i < sublevel.getMap().size(); i++)
//	{
//		for (int j = 0; j < sublevel.getMap()[i].size(); j++)
//		{
//			sublevel.getMap()[i][j]->update(elapsedTime);
//			sublevel.getMap()[i][j]->draw(win);
//		}
//	}
//	if(DEBUG_GENERATION_DRAW) //чтобы успевать увидеть что отрисовалось
//	{
//		//Sleep(70);
//	}
//}
void drawSublevel(Sublevel & sublevel, sf::RenderWindow & win)
{
	for (int i = 0; i < sublevel.getMap().size(); i++)
	{
		for (int j = 0; j < sublevel.getMap()[i].size(); j++)
		{
			sublevel.getMap()[i][j]->draw(win);
		}
	}
}
void updateSublevel(Sublevel & sublevel, float elapsedTime)
{
	for (int i = 0; i < sublevel.getMap().size(); i++)
	{
		for (int j = 0; j < sublevel.getMap()[i].size(); j++)
		{
			sublevel.getMap()[i][j]->update(elapsedTime);
			
		}
	}

}
void drawLevel(vector<Sublevel> & level, sf::RenderWindow & win)
{
	for (int i = 0; i < level.size(); i++)
	{
		drawSublevel(level[i], win);
	}
}

enum sublevelLineState
{
	start, rightEnterLeftExit, leftEnterRightExit
};

class Level
{
protected:
	vector<Sublevel> level; //вектор подуровней, в котором каждый подуровень знает, в какой координате его отрисовать
	ResourceManager rm; //класс для хранением картинок/спрайтов и т.д. Разные блоки могут использовать один и тот же спрайт. Этот класс занимается их распределением.
public:
	Level();
	Content * player;
	Sublevel & findSublevel(size_t x, size_t y);
	int levelLenght; //количество подуровней по горизонтали
	vector<Sublevel> & getLevelMap();
	void draw(sf::RenderWindow & win);
	void update(float elapsedTime);
	~Level();
};

