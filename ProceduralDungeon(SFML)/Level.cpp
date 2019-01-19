#include "Level.h"
#include "Player.h"
#include "Guntrap.h"

Level::Level() //в этом конструкторе находится основная часть алгортима процедурной генерации карты. он получился огромезный, но смысла разделять на функции я не вижу, потому что больше это ни где не используется
{
	sublevelLineState state; //старт - создается линия подуровней без изначального входа, но с выходом справа снизу.
	//rightEnterLeftExit - создается линия подуровней с входом срправа сверху и выходом слева снизу
	//leftEnterRightExit - наоборот
	LevelGenerationState generationState = normal; //переменная, отвечающая за попадание в ситуацию бесконечного цикла в конструкторах подуровней. Если такое случается, то уровень будет пересоздан заново.
	size_t lx;
	size_t ly;
	float enterX; //изначальные позиции выхода из текущего-входа в следующий 
	float enterY;
	vector<int> sublevelHorizontalLineHeight; //вектор для хранения суммы высот каждого подуровня по вертикали. Необходим для того, чтобы знать на какой коориднате по y делать подуровень
	Sublevel sub;
	int lenght = 0; //длина первой линии из подуровней по горизонтали
	do //данный цикл необходим для обработки вхождения конструкторов Sublevel в состояние бесконечного цикла. Это бывает, когда не получается создать подуровень с проходами между соседними
		//из-за несостыковки по высоте. То есть, в одном столбике создались подуровени с слишком большими высотами, а в другом слишком маленькими. В таком случае конструктор подуровня отправляет
		// в generationState значение restart и выходит из цикла. По умолчанию переменная равна normal, но потому что это do while цикл отработает один раз.
	{
		if (DEBUG_GENERATION_DRAW == true)
		{
			system("cls");
		}
		state = start; //первым сработает первый кейс в свиче
		generationState = normal; //ставлю состояние генерации в нормальное
		lx = 0;
		ly = 0;
		enterX = -1; //координаты -1 не может быть, по этому это будет изначальной координатой входа
		enterY = -1;
		level.clear();
		sublevelHorizontalLineHeight.clear();
		sub = Sublevel(lx, ly, right_, exit_, generationState, rm); //создаю первую стартовую комнату, в которой будет только выход
		lenght = 0;
		if (DEBUG_GENERATION_DRAW) //отрисовка подуровней нагорячую прямо во время создания уровня. Необходимо было чтобы понять где именно появлялся бесконечный цикл. Оставил, потому что красиво выглядит )
		{
			//drawSublevel(sub);
		}

		do //данный цикл необходим для чередования линий из подуровней. То есть вход справа сверху, выход снизу слева и вход слева сверху и выход справа снизу
			//цикл необходим из-за того, что неизвестно сколько именно подуровней может поместится по высоте т.е. не известно количество чередований rightEnterLeftExit и leftEnterRightExit
			//start отработает один раз и больше в свич в него не зайдет
		{
			switch (state)
			{
			case start: //на этапе старта создается самая первая линия из подуровней с произвольной шириной и высотой. В других кейсах произвольной будет только высота.
			{
				while (lx < X_SIZE - 3)
				{
					level.push_back(sub);
					if (DEBUG_GENERATION_DRAW) //отрисовка подуровней нагорячую прямо во время создания уровня. Необходимо было чтобы понять где именно появлялся бесконечный цикл. Оставил, потому что красиво выглядит )
					{
						//drawSublevel(sub);
					}
					sublevelHorizontalLineHeight.push_back(sub.getHeight()); //заполняю вектор высот
					lx += sub.getWidth();
					enterX = sub.getExitPosX(); 
					enterY = sub.getExitPosY();
					sub = Sublevel(lx, ly, 0, enterY, 0, generationState, rm);

					if(generationState == restart)
					{
						break;
					}
					
					sub.addExit(right_, rm);
					lenght++;
				}
				if (generationState == restart)
				{
					break;
				}
				Block * block = (Block*)level[lenght - 1].getMap()[level[lenght - 1].getExitPosY()][level[lenght - 1].getExitPosX()]; //убераю старый выход в бок, вместо него ставлю стену
				block->setBlockType(brick, rm);
				level[lenght - 1].getMap()[level[lenght - 1].getExitPosY()][level[lenght - 1].getExitPosX()] = block;

				level[lenght - 1].addExit(down, rm); //теперь делаю новый выход уже вниз
				level[lenght - 1].makeItAngle();
				if(DEBUG_GENERATION_DRAW) //отрисовка подуровней нагорячую прямо во время создания уровня. Необходимо было чтобы понять где именно появлялся бесконечный цикл. Оставил, потому что красиво выглядит )
				{
					//drawSublevel(level[lenght - 1]);
				}
				state = rightEnterLeftExit;
				enterX = level[lenght - 1].getExitPosX();
				enterY = level[lenght - 1].getExitPosY();
			}
			break;
			case rightEnterLeftExit:
			{
				sub = Sublevel(level[lenght - 1].getX(), sublevelHorizontalLineHeight[lenght - 1], level[lenght - 1].getWidth(), enterX, 0, 0, generationState, y_sided, rm);
				sublevelHorizontalLineHeight[lenght - 1] += sub.getHeight(); //увеличиваю высоту горизонтали подуровней за счет высоты нового подуровня. Теперь это будет новым y для следующего подуровня
				sub.addExit(left_, rm); //добавляю выход в левую стенку подуровня
				enterX = sub.getExitPosX(); //получаю координаты выхода из этого подуровня
				enterY = sub.getExitPosY();
				//level.insert(level.begin() + lenght, sub);
				if (DEBUG_GENERATION_DRAW) //отрисовка подуровней нагорячую прямо во время создания уровня. Необходимо было чтобы понять где именно появлялся бесконечный цикл. Оставил, потому что красиво выглядит )
				{
					//drawSublevel(sub);
				}
				level.push_back(sub);
				for (int i = lenght - 2; i >= 0; i--)
				{
					sub.getExitGlobalCoords(enterX, enterY); //получаю координаты выхода из прошлого подуровня в масштабе всего уровня(то есть, не относительно начала подуровня)
					sub = Sublevel(level[i].getX(), sublevelHorizontalLineHeight[i], level[i].getWidth(), level[i].getWidth() - 1, enterY / COMMON_SPRITE_SIZE - sublevelHorizontalLineHeight[i], 0, generationState, x_sided, rm);
					//первый аргумент это x позиция верхнего подуровня, 
					//второй это текущия позиция данного столбика из вектора высот, 
					//третий это ширина верхнего подуровня(в это она не будет рандомится) в отличии от высоты
					//четвертый это ширина-1 т.е. позиция входа в подуровень по X(то есть самая правая стенка)
					//пятый это разница между глобальной координатой выхода из прошлого подуровня и текущей высотой этого столбика подуровней - в результате получается координата относительно начала этого подуровня
					//шестой 0 - тип прохода в подуровне - вход
					//относительные координаты выхода/входа нужны из-за цикла в конструкторе подуровня, который расставляет блоки в зависимости от текущих значений i и j которые начинаются от нуля
					if (generationState == restart)
					{
						break;
					}
					sublevelHorizontalLineHeight[i] += sub.getHeight(); //увеличиваю высоту горизонтали подуровней за счет высоты нового подуровня. Теперь это будет новым y для следующего подуровня
					sub.addExit(left_, rm); //добавляю выход в новый подуровень
				//	level.insert(level.begin() + lenght + 1, sub); //добавляю новый подуровень в вектор
					if (DEBUG_GENERATION_DRAW) //отрисовка подуровней нагорячую прямо во время создания уровня. Необходимо было чтобы понять где именно появлялся бесконечный цикл. Оставил, потому что красиво выглядит )
					{
						//drawSublevel(sub);
					}
					level.push_back(sub);
				}
				if (generationState == restart)
				{
					break;
				}
				//убераю старый выход влево, вместо него делаю выход вниз
				Block * block = (Block*)level[level.size()-1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()]; //убераю старый выход в бок, вместо него ставлю стену
				block->setBlockType(brick, rm);
				level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()] = block;

				level[level.size() - 1].makeItAngle();

				level[level.size() - 1].addExit(down, rm); //теперь делаю новый выход уже вниз
				enterX = level[level.size() - 1].getExitPosX(); //получаю координаты выхода из этого подуровня
				enterY = level[level.size() - 1].getExitPosY();
				state = leftEnterRightExit;//изменяю состояние линии подуровней на начало слева
				if (DEBUG_GENERATION_DRAW) //отрисовка подуровней нагорячую прямо во время создания уровня. Необходимо было чтобы понять где именно появлялся бесконечный цикл. Оставил, потому что красиво выглядит )
				{
					//drawSublevel(level[level.size() - 1]);
				}
			}
				break;
			case leftEnterRightExit:
			{
				sub = Sublevel(level[0].getX(), sublevelHorizontalLineHeight[0], level[0].getWidth(), enterX, 0, 0, generationState, y_sided, rm);
				sublevelHorizontalLineHeight[0] += sub.getHeight(); //увеличиваю высоту горизонтали подуровней за счет высоты нового подуровня. Теперь это будет новым y для следующего подуровня
				sub.addExit(right_, rm); //добавляю выход в левую стенку подуровня
				//level.insert(level.begin() + lenght, sub);
				level.push_back(sub);
				if (DEBUG_GENERATION_DRAW) //отрисовка подуровней нагорячую прямо во время создания уровня. Необходимо было чтобы понять где именно появлялся бесконечный цикл. Оставил, потому что красиво выглядит )
				{
					//drawSublevel(sub);
				}
				for (int i = 1; i < lenght; i++)
				{
					sub.getExitGlobalCoords(enterX, enterY); //получаю координаты выхода из прошлого подуровня в масштабе всего уровня(то есть, не относительно начала подуровня)
					sub = Sublevel(level[i].getX(), sublevelHorizontalLineHeight[i], level[i].getWidth(), 0, enterY / COMMON_SPRITE_SIZE - sublevelHorizontalLineHeight[i], 0, generationState, x_sided, rm);
				
					//первый аргумент это x позиция верхнего подуровня, 
					//второй это текущия позиция данного столбика из вектора высот, 
					//третий это ширина верхнего подуровня(в это она не будет рандомится) в отличии от высоты
					//четвертый это ширина-1 т.е. позиция входа в подуровень по X(то есть самая правая стенка)
					//пятый это разница между глобальной координатой выхода из прошлого подуровня и текущей высотой этого столбика подуровней - в результате получается координата относительно начала этого подуровня
					//шестой 0 - тип прохода в подуровне - вход
					//относительные координаты выхода/входа нужны из-за цикла в конструкторе подуровня, который расставляет блоки в зависимости от текущих значений i и j которые начинаются от нуля
					if (generationState == restart)
					{
						break;
					}
					sublevelHorizontalLineHeight[i] += sub.getHeight(); //увеличиваю высоту горизонтали подуровней за счет высоты нового подуровня. Теперь это будет новым y для следующего подуровня
					sub.addExit(right_, rm); //добавляю выход в новый подуровень
					enterX = sub.getExitPosX(); //получаю координаты выхода из этого подуровня
					enterY = sub.getExitPosY();
					//level.insert(level.begin() + lenght, sub); //добавляю новый подуровень в вектор
					if (DEBUG_GENERATION_DRAW) //отрисовка подуровней нагорячую прямо во время создания уровня. Необходимо было чтобы понять где именно появлялся бесконечный цикл. Оставил, потому что красиво выглядит )
					{
						//drawSublevel(sub);
					}
					level.push_back(sub);
				}
				if (generationState == restart)
				{
					break;
				}
				//меняю выход из бокового в нижний справа
				Block * block = (Block*)level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()]; //убераю старый выход в бок, вместо него ставлю стену
				block->setBlockType(brick, rm);
				level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()] = block;

				level[level.size() - 1].addExit(down, rm); //теперь делаю новый выход уже вниз

				level[level.size() - 1].makeItAngle();

				enterX = level[level.size() - 1].getExitPosX(); //получаю координаты выхода из этого подуровня
				enterY = level[level.size() - 1].getExitPosY();
				state = rightEnterLeftExit;
				if (DEBUG_GENERATION_DRAW) //отрисовка подуровней нагорячую прямо во время создания уровня. Необходимо было чтобы понять где именно появлялся бесконечный цикл. Оставил, потому что красиво выглядит )
				{
					//drawSublevel(level[level.size() - 1]);
				}
			}
				break;
			default:
				break;
			}
		} while (sublevelHorizontalLineHeight[0] < Y_SIZE - 3 && generationState != restart);
		Block * block = (Block*)level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()]; //убераю старый выход
		block->setBlockType(brick, rm);
		level[level.size() - 1].makeItAngle();
		level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()] = block;
	} while (generationState == restart);
	for(int i = 0; i < level.size()-1; i++)
	{
		level[i].next = level[i+1].getPointer();
	}
	for(int i = 0; i < level.size();i++)
	{
		if(!level[i].isAngle())
		{
			level[i].fill(guntrapped_vertical, rm);
		}
	}
	player = new Player((level[0].getWidth() / 2) * COMMON_SPRITE_SIZE, (level[0].getHeight() / 2) * COMMON_SPRITE_SIZE, &level[0], rm);
	level[0].addContent(player);
	
	/*level[0].addContent(new Guntrap((level[0].getWidth() / 2)*COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE, rm, top, &level[0]));
	level[0].addContent(new Guntrap((level[0].getWidth() / 2)*COMMON_SPRITE_SIZE, (level[0].getHeight()-1) * COMMON_SPRITE_SIZE, rm, down, &level[0]));
	level[0].addContent(new Guntrap(COMMON_SPRITE_SIZE, (level[0].getHeight() / 2) * COMMON_SPRITE_SIZE, rm, left_, &level[0]));*/
}
Sublevel & Level::findSublevel(size_t x, size_t y)
{
	for(int subIterator = 0; subIterator < level.size(); subIterator++)
	{
		for(int i = 0; i < level[subIterator].getMap().size(); i++)
		{
			for (int j = 0; j < level[subIterator].getMap()[i].size(); j++)
			{
				if(level[subIterator].getMap()[i][j]->getX() == x && level[subIterator].getMap()[i][j]->getY() == y)
				{
					return level[subIterator];
				}
			}
		}
	}
}
vector<Sublevel> & Level::getLevelMap()
{
	return level;
}

void Level::draw(sf::RenderWindow & win)
{
	for (int i = 0; i < level.size(); i++)
	{
		drawSublevel(level[i], win);
	}
}
void Level::update(float elapsedTime)
{
	for (int i = 0; i < level.size(); i++)
	{
		updateSublevel(level[i], elapsedTime);
	}
}
Level::~Level()
{
}
