#pragma once
#include "Sublevel.h"

enum sublevelLineState
{
	start, rightEnterLeftExit, leftEnterRightExit
};

class Level
{
protected:
	vector<Sublevel> level; //вектор подуровней, в котором каждый подуровень знает, в какой координате его отрисовать
	ResourceManager rm; //класс для хранением картинок/спрайтов и т.д. Разные блоки могут использовать один и тот же спрайт. Этот класс занимается их распределением.
	size_t levelHeight; //примерная высота и ширина уровня
	size_t levelWidth;
public:
	Level(size_t levelWidth, size_t levelHeight);
	Content * player; //указатель на игрока, нужен для удобного доступа к его координатам извне
	int getPlayerTries();//функция получения попыток(жизней игрока)
	ResourceManager & getResourceManager();
	int levelLenght; //количество подуровней по горизонтали
	vector<Sublevel> & getLevelMap();
	void draw(sf::RenderWindow & win);
	void update(float elapsedTime);
	~Level();
};

