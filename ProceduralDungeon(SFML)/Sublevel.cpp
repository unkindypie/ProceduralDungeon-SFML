#include "Sublevel.h"
#include "Guntrap.h"
#include "Blade.h"

int randomNumber(int minNum, int maxNum) {
	int result;
	int lowNum = 0;
	int hiNum = 0;
	if (minNum < maxNum) {
		lowNum = minNum;
		hiNum = maxNum + 1;
	}
	else {
		lowNum = maxNum + 1;
		hiNum = minNum;
	}
	result = (rand() % (hiNum - lowNum)) + lowNum;
	return result;
}

Sublevel::Sublevel()
{

}
Sublevel::~Sublevel()
{

}
Sublevel::Sublevel(size_t x, size_t y, size_t holeCoordX, size_t holeCoordY, bool holeType, LevelGenerationState & gState, ResourceManager & rm)  //конструктор для создания подуровня с отверствием с одной стороны(holeType = 0 - вход, 1 - выход)
{
	bool doesHoleExist = 0;
	size_t iterationsCounter = 0;
	while(!doesHoleExist || enterPosX > width || enterPosY >= height-2 || enterPosY < 1){ 
		iterationsCounter++;
		if (iterationsCounter > MAX_RAND_LOOP_COUNT) //в случае если конструктор вошел в бесконечный цикл, то выхожу из него и пересоздаю сам уровень
		{
			gState = restart;
			break;
		}
		map.clear();
		this->x = x;
		this->y = y;

		if(holeType)//в зависимости от того, вход это или выход записываю координаты в сооветсвующие переменные
		{
			exitPosX = holeCoordX;
			exitPosY = holeCoordY;
		}
		else
		{
			enterPosX = holeCoordX;
			enterPosY = holeCoordY;
		}
		int times = 0; //переменная нужна для того случая, когда минимальный размер подуровня при добавлении увеличивает размер карты до такой степени, что
		//не получается создать карту меньше определенного размера и программа входит в бесконечный цикл
		do //ширина
		{
			width = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
			times++;
		} while (width + x > X_SIZE && times < MAX_RAND_LOOP_COUNT); //пока размеры не подходят условию и количество итераций меньше маскимального
		times = 0;
		do//высота
		{
			height = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
			times++;
		} while (height + y > Y_SIZE && times < MAX_RAND_LOOP_COUNT);

		for (int i = 0; i < height; i++) //делаю двумерный вектор указателей абстрактного класса Content
		{
			map.push_back(vector<Content*>(width));
		}
		for (int i = 0; i < height; i++)  //цикл прохода по массиву для проставления границ
		{
			for (int j = 0; j < width; j++)
			{
				if (i == 0 || j == 0 || j == width - 1 || i == height - 1)//если это граница, то ставлю кирпичи
				{
					map[i][j] = new Block((x + j) * COMMON_SPRITE_SIZE, (y + i) * COMMON_SPRITE_SIZE, brick, rm);
				}
				else//если нет, то пустоту
				{
					map[i][j] = new Block((x + j) * COMMON_SPRITE_SIZE, (y + i) * COMMON_SPRITE_SIZE, none, rm);
				}
				if(i == holeCoordY && j == holeCoordX)//выход из подуровня
				{
					map[i][j] = new Block((x + j) * COMMON_SPRITE_SIZE, (y + i) * COMMON_SPRITE_SIZE, none, rm);
					doesHoleExist = 1;
					if (holeType)
					{
						exitRect = map[i][j]->getRect();
					}
					else
					{
						enterRect = map[i][j]->getRect();
					}
				}
			}
		}
	}
}
Sublevel::Sublevel(size_t x, size_t y, int lastWidth, size_t holeCoordX, size_t holeCoordY, bool holeType, LevelGenerationState & gState, HoleDestenation holeDestenation, ResourceManager & rm) //фиксированая ширина и координата входа
{
	bool doesHoleExist = 0; //в случае, если не получилось добавить проход, то эта переменная равна нулю. Пока она ноль, цикл будет пересоздавать подуровень

	size_t iterationsCounter = 0; //счетчик итераций цикла. Если их становится больше, чем константа MAX_RAND_LOOP_COUNT, то цикл стал бесконечным, 
	//а значит изначальные координаты уже не дают возможности создать подуровень и пора пересоздавать уровень заново.

	//максимальные и минимальные координаты для входа/выхода
	int minimalXHolePos = 0;
	int minimalYHolePos = 0;
	int maximumXHolePos = width;
	int maximumYHolePos = height;

	if(holeDestenation == x_sided) //в зависимисоти от того, какой оси будет пренадлежать проход, противоположная координата должна будет пропускать 0 и край чтобы небыло так, 
		//чтоб проход оказался внутри стенки в углу. Ну вообщем если убрать этот if и откомпилировать, то будет видно, о чем я говорю.  
	{
		maximumYHolePos = height - 2;
		maximumXHolePos = width;
		minimalYHolePos = 1;
	}
	else
	{
		maximumXHolePos = width - 2;
		maximumYHolePos = height;
		minimalXHolePos = 1;
	}
	while (!doesHoleExist || enterPosX > maximumXHolePos  || enterPosX < minimalXHolePos || enterPosY > maximumYHolePos || enterPosY < minimalYHolePos) {
		iterationsCounter++;
		if(iterationsCounter > MAX_RAND_LOOP_COUNT) //в случае если конструктор вошел в бесконечный цикл, то выхожу из него и пересоздаю сам уровень
		{
			gState = restart;
			break;
		}
		map.clear();
		this->x = x;
		this->y = y;

		if (holeType)//в зависимости от того, вход это или выход записываю координаты в сооветсвующие переменные
		{
			exitPosX = holeCoordX;
			exitPosY = holeCoordY;
		}
		else
		{
			enterPosX = holeCoordX;
			enterPosY = holeCoordY;
		}
		int times = 0; //переменная нужна для того случая, когда минимальный размер подуровня при добавлении увеличивает размер карты до такой степени, что
		//не получается создать карту меньше определенного размера и программа входит в бесконечный цикл

		width = lastWidth; 
		times = 0;
		do//высота
		{
			height = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
			times++;
		} while (height + y > Y_SIZE && times < MAX_RAND_LOOP_COUNT);
		
		for (int i = 0; i < height; i++) //делаю двумерный вектор указателей абстрактного класса Content
		{
			map.push_back(vector<Content*>(width));
		}
		for (int i = 0; i < height; i++)  //цикл прохода по массиву для проставления границ
		{
			for (int j = 0; j < width; j++)
			{
				if (i == 0 || j == 0 || j == width - 1 || i == height - 1)//если это граница, то ставлю кирпичи
				{
					map[i][j] = new Block((x + j) * COMMON_SPRITE_SIZE, (y + i) * COMMON_SPRITE_SIZE, brick, rm);
				}
				else//если нет, то пустоту
				{
					map[i][j] = new Block((x + j) * COMMON_SPRITE_SIZE, (y + i) * COMMON_SPRITE_SIZE, none, rm);
				}
				if (i == holeCoordY && j == holeCoordX)//выход из подуровня
				{
					map[i][j] = new Block((x + j) * COMMON_SPRITE_SIZE, (y + i) * COMMON_SPRITE_SIZE, none, rm);
					doesHoleExist = 1;
					if (holeType)
					{
						exitRect = map[i][j]->getRect();
					}
					else
					{
						enterRect = map[i][j]->getRect();
					}
				}
			}
		}
		if (holeDestenation == x_sided) //высота изменилась, надо обновить границы проходов на случай, если цикл отработает еще раз
		{
			maximumYHolePos = height - 2;
			maximumXHolePos = width;
			minimalXHolePos = 0;
			minimalYHolePos = 1;
		}
		else
		{
			maximumXHolePos = width - 2;
			maximumYHolePos = height;
			minimalXHolePos = 1;
			minimalYHolePos = 0;

		}
	}
}


Sublevel::Sublevel(size_t x, size_t y, direction holePosition, holeMode mode, LevelGenerationState & gState, ResourceManager & rm) //конструктор для создания подуровня с отверствиями(holeType = 0 - вход, 1 - выход)
{
	this->x = x;
	this->y = y;
	
	int times = 0; //переменная нужна для того случая, когда минимальный размер подуровня при добавлении увеличивает размер карты до такой степени, что
	//не получается создать карту меньше определенного размера и программа входит в бесконечный цикл
	do //ширина
	{
		width = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
		times++;
		if(times > MAX_RAND_LOOP_COUNT)
		{
			gState = restart;
			break;
		}
	} while (width + x > X_SIZE); //пока размеры не подходят условию и количество итераций меньше маскимального
	times = 0;
	do//высота
	{
		height = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
		times++;
		if (times > MAX_RAND_LOOP_COUNT)
		{
			gState = restart;
			break;
		}
	} while (height + y > Y_SIZE);
	//генерация координат входа и выхода
	switch (mode)
	{
	case enter:
		generateEnterExit(enterPosX, enterPosY, width, height, holePosition);
		break;
	case exit_:
		generateEnterExit(exitPosX, exitPosY, width, height, holePosition);
		break;
	default:
		break;
	}

	for (int i = 0; i < height; i++) //делаю двумерный вектор указателей абстрактного класса Content
	{
		map.push_back(vector<Content*>(width));
	}
	for (int i = 0; i < height; i++)  //цикл прохода по массиву для проставления границ
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || j == 0 || j == width - 1 || i == height - 1)//если это граница, то ставлю кирпичи
			{
				map[i][j] = new Block((x + j) * COMMON_SPRITE_SIZE, (y + i) * COMMON_SPRITE_SIZE, brick, rm);
			}
			else //если нет, то пустоту
			{
				map[i][j] = new Block((x + j) * COMMON_SPRITE_SIZE, (y + i) * COMMON_SPRITE_SIZE, none, rm);
			}
			if (i == enterPosY && j == enterPosX || i == exitPosY && j == exitPosX) //ставлю выход либо вход
			{
				map[i][j] = new Block((x + j) * COMMON_SPRITE_SIZE, (y + i) * COMMON_SPRITE_SIZE, none, rm);
				if(mode==enter)	enterRect = map[i][j]->getRect();
				if(mode==exit_) exitRect = map[i][j]->getRect();
			}
		}
	}
}
void Sublevel::generateEnterExit(int & coordX, int & coordY, size_t width, size_t height, direction holePosition) //функция генерации координат проходов конкретно в массиве(без учета координат отрисовки на экран)
{
	switch (holePosition) //от этого свича зависит позиция
	{
	case left_:

		coordY = randomNumber(3, height-2);
		coordX = 0;
		break;
	case right_:
		coordY = randomNumber(3, height-2);
		coordX = width-1;
		break;
	case top:
		coordY = 0;
		coordX = randomNumber(3, width-2);
		break;
	case down:
		coordY = height-1;
		coordX = randomNumber(3, width-2);
		break;
	default:
		break;
	}
}
void Sublevel::getExitGlobalCoords(float & x, float & y) //возвращаю координаты контента, который лежит в этой позиции масива
{
	x = map[exitPosY][exitPosX]->getX();
	y = map[exitPosY][exitPosX]->getY();
}
void Sublevel::getEnterGlobalCoords(float & x, float & y) //возвращаю координаты контента, который лежит в этой позиции масива
{
	x = map[enterPosY][enterPosX]->getX();
	y = map[enterPosY][enterPosX]->getY();
}
void Sublevel::makeItAngle()
{
	angle = true;
}
bool Sublevel::isAngle()
{
	return angle;
}
void Sublevel::addContent(Content * c)
{
	map[height-1].push_back(c);
}
void Sublevel::addExit(direction holePosition, ResourceManager & rm)
{
	generateEnterExit(exitPosX, exitPosY, width, height, holePosition); //генерирую координаты
	map[exitPosY][exitPosX] = new Block((x + exitPosX) * COMMON_SPRITE_SIZE, (y + exitPosY) * COMMON_SPRITE_SIZE, none, rm); //ставлю по ним пустой блок
	exitRect = map[exitPosY][exitPosX]->getRect();
}
void Sublevel::addEnter(direction holePosition, ResourceManager & rm)
{
	generateEnterExit(enterPosX, enterPosY, width, height, holePosition); //генерирую координаты
	map[enterPosY][enterPosX] = new Block((x + enterPosX) * COMMON_SPRITE_SIZE, (y + enterPosY) * COMMON_SPRITE_SIZE, none, rm); //ставлю по ним пустой блок
	enterRect = map[enterPosY][enterPosX]->getRect();
	
}
vector<Content*>::iterator Sublevel::getContentIterator(Content * cont) //поиск итератора на контент в векторе(который не вектор векторов, а именно вектор)
{
	
	for (vector<vector<Content*>>::iterator i = map.begin(); i != map.end(); i++)
	{
		//return find((*i).begin(), (*i).end(), cont);
		for(vector<Content*>::iterator j = (*i).begin(); j != (*i).end(); j++)
		{
			if((*j)==cont)
			{
				return j;
			}
		}
	}
}
void Sublevel::fill(SublevelFillingType ft, ResourceManager & rm)
{
	bool rn;
	int dirX;
	int dirY;

	switch (ft)
	{
	case first:
		fillingType = ft;
		break;
	case last:
		fillingType = ft;
		break;
	case clean:
		fillingType = ft;
		break;
	case guntrapped_vertical:
		fillingType = ft;
		for(int i = 2; i < width-2; i++)
		{
			rn = randomNumber(0, 1);
			

			if(rn) addContent(new Guntrap((x + i)*COMMON_SPRITE_SIZE, y * COMMON_SPRITE_SIZE + COMMON_SPRITE_SIZE, rm, top, this));
		}
		break;
	case guntrapped_horizontal:
		fillingType = ft;
		break;
	case razer:
		fillingType = ft;
		rn = randomNumber(1, 5);
		for (int i = 0; i < rn; i++)
		{
			do
			{
				dirX = randomNumber(-1, 1);
				dirY = randomNumber(-1, 1);

			} while (!dirX || !dirY);
			addContent(new Blade((randomNumber(width/3, width-2)+x)*COMMON_SPRITE_SIZE, (randomNumber(height / 3, height - 2)+y) * COMMON_SPRITE_SIZE, this, rm, dirX, dirY));
		}
		break;
	default:
		break;
	}
}
sf::FloatRect Sublevel::getExitRect()
{
	return exitRect;
}
sf::FloatRect Sublevel::getEnterRect()
{
	return enterRect;
}
size_t Sublevel::getX()
{
	return x;
}
size_t Sublevel::getY()
{
	return y;
}
size_t Sublevel::getHeight()
{
	return height;
}
size_t Sublevel::getWidth()
{
	return width;
}
size_t Sublevel::getEnterPosX()
{
	return enterPosX;
}
size_t Sublevel::getEnterPosY()
{
	return enterPosY;
}
size_t Sublevel::getExitPosX()
{
	return exitPosX;
}
size_t Sublevel::getExitPosY()
{
	return exitPosY;
}
vector<vector<Content*>> & Sublevel::getMap()
{
	return map;
}
Sublevel * Sublevel::getPointer()
{
	return this;
}
