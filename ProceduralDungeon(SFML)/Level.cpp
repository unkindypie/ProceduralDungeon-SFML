#include "Level.h"
#include "Player.h"
#include "Guntrap.h"
#include "Blade.h"
Level::Level()
{
	Sublevel::X_SIZE = levelWidth = 1000000;
	Sublevel::Y_SIZE = levelHeight = 720 / 32;
	LevelGenerationState gs = normal;
	Sublevel sub = Sublevel(0, 0, right_, exit_, gs, rm);
	level.push_back(sub);
	int lastWidth = level[level.size() - 1].getWidth();
	for(int i = 0; i < 20; i++){
		sub = Sublevel(lastWidth, 0, 0, level[level.size() - 1].getExitPosY(), 0, gs, rm);
		sub.addExit(right_, rm);
		level.push_back(sub);
		lastWidth += sub.getWidth();
	}
	for (int i = 0; i < level.size() - 1; i++)
	{
		level[i].next = &level[i + 1];
	}
	for (int i = level.size() - 1; i > 0; i--)
	{
		level[i].prev = &level[i - 1];
	}
	

	player = new Player((level[0].getWidth() / 2) * COMMON_SPRITE_SIZE, (level[0].getHeight() / 2) * COMMON_SPRITE_SIZE, &level[0], rm);

	level[0].addEntity(player);
}
Level::Level(size_t levelWidth, size_t levelHeight) //в этом конструкторе находится основная часть алгортима процедурной генерации карты. он получился огромезный, но смысла разделять на функции я не вижу, потому что больше это ни где не используется
{
	Sublevel::X_SIZE = levelHeight;
	Sublevel::Y_SIZE = levelWidth;
	this->levelHeight = levelHeight;
	this->levelWidth = levelWidth;
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

		do //данный цикл необходим для чередования линий из подуровней. То есть вход справа сверху, выход снизу слева и вход слева сверху и выход справа снизу
			//цикл необходим из-за того, что неизвестно сколько именно подуровней может поместится по высоте т.е. не известно количество чередований rightEnterLeftExit и leftEnterRightExit
			//start отработает один раз и больше в свич в него не зайдет
		{
			switch (state)
			{
			case start: //на этапе старта создается самая первая линия из подуровней с произвольной шириной и высотой. В других кейсах произвольной будет только высота.
			{
				while (lx < levelWidth - 3)
				{
					level.push_back(sub);
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
				dynamic_cast<Block*>(level[lenght - 1].getMap()[level[lenght - 1].getExitPosY()][level[lenght - 1].getExitPosX()])->setBlockType(brick, rm, right_);
			

				level[lenght - 1].addExit(down, rm); //теперь делаю новый выход уже вниз
				level[lenght - 1].makeItAngle();
			
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
				
					level.push_back(sub);
				}
				if (generationState == restart)
				{
					break;
				}

				//убераю старый выход влево, вместо него делаю выход вниз
				dynamic_cast<Block*>(level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()])->setBlockType(brick, rm, left_);
				
				level[level.size() - 1].makeItAngle(); //делаю этот подуровень угловым(в нем не будут ставиться ловушки)

				level[level.size() - 1].addExit(down, rm); //теперь делаю новый выход уже вниз

				enterX = level[level.size() - 1].getExitPosX(); //получаю координаты выхода из этого подуровня
				enterY = level[level.size() - 1].getExitPosY();
				state = leftEnterRightExit;//изменяю состояние линии подуровней на начало слева
			}
				break;
			case leftEnterRightExit:
			{
				sub = Sublevel(level[0].getX(), sublevelHorizontalLineHeight[0], level[0].getWidth(), enterX, 0, 0, generationState, y_sided, rm);
				sublevelHorizontalLineHeight[0] += sub.getHeight(); //увеличиваю высоту горизонтали подуровней за счет высоты нового подуровня. Теперь это будет новым y для следующего подуровня
				sub.addExit(right_, rm); //добавляю выход в левую стенку подуровня
				//level.insert(level.begin() + lenght, sub);
				level.push_back(sub);

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
					level.push_back(sub);
				}
				if (generationState == restart)
				{
					break;
				}
				//меняю выход из бокового в нижний справа
				dynamic_cast<Block*>(level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()])->setBlockType(brick, rm, right_);

				level[level.size() - 1].addExit(down, rm); //теперь делаю новый выход уже вниз

				level[level.size() - 1].makeItAngle();

				enterX = level[level.size() - 1].getExitPosX(); //получаю координаты выхода из этого подуровня
				enterY = level[level.size() - 1].getExitPosY();
				state = rightEnterLeftExit;
			}
				break;
			default:
				break;
			}
		} while (sublevelHorizontalLineHeight[0] < levelHeight - 3 && generationState != restart);

		dynamic_cast<Block*>(level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()])->setBlockType(brick, rm, down);

		level[level.size() - 1].makeItAngle();


	} while (generationState == restart);

	for(int i = 0; i < level.size()-1; i++)
	{
		level[i].next = &level[i + 1];
	}
	for (int i = level.size() - 1; i > 0 ; i--)
	{
		level[i].prev = &level[i - 1];
	}
	SublevelFillingType stype;
	for(int i = 1; i < level.size();i++)
	{
		if(!level[i].isAngle())
		{
			stype = SublevelFillingType(randomNumber(0, 3));
			if(stype > 0)
			{
				level[i].fill(guntrapped_vertical, rm);
			}
			else
			{
				level[i].fill(razer, rm);
			}
			
		}
	}
	player = new Player((level[0].getWidth() / 2) * COMMON_SPRITE_SIZE, (level[0].getHeight() / 2) * COMMON_SPRITE_SIZE, &level[0], rm);
	level[0].addEntity(player);
	//size_t pos = level.size()-2;
	//player = new Player((level[pos].getWidth() / 2) * COMMON_SPRITE_SIZE, (level[pos].getHeight() / 2) * COMMON_SPRITE_SIZE, &level[pos], rm);
	//level[pos].addContent(player);
	
	
}

ResourceManager & Level::getResourceManager()
{
	return rm;
}
int Level::getPlayerTries()
{
	return dynamic_cast<Player*>(player)->getTries();
}
vector<Sublevel> & Level::getLevelMap()
{
	return level;
}
void Level::draw(sf::RenderWindow & win)
{
	//основная идея в том, чтобы цикл отрисовки ходил только по тем блокам, которые заведомо влазят в поле зрения, а не проверял это походу дела, проходя по всем сразу
	sf::FloatRect viewRect = { win.getView().getCenter().x - win.getSize().x / 2, win.getView().getCenter().y - win.getSize().y / 2, (float)win.getSize().x, (float)win.getSize().y };//получаю прямоугольник вида
	for (int sub = 0; sub < level.size(); sub++) //проход по вектору подуровней уровня
	{
		//получаю координаты вида(поля зрения) в виде блоков, а не пикселей
		int startY = viewRect.top / COMMON_SPRITE_SIZE;
		int endY = (viewRect.top + viewRect.height) / COMMON_SPRITE_SIZE;
		int startX = viewRect.left / COMMON_SPRITE_SIZE;
		int endX = (viewRect.left + viewRect.width) / COMMON_SPRITE_SIZE;
		if (startY < 0) startY = 0;
		if (startX < 0) startX = 0;
		//тут должна быть проверка на выход координат вида за пределы уровня. Но я никому не расскажу, что ее здесь нет
		
		//если подуровень находится за координатами вида, то пропускаю итерацию
		if (startY >= level[sub].getY() + level[sub].getHeight() || endY <= level[sub].getY()
			|| startX >= level[sub].getX() + level[sub].getWidth() || endX <= level[sub].getX()) continue;

		//получаю конкретное пересечение подуровней с видом, дабы далее идти циклом только по тем блокам, которые находятся в поле зрения
		int beginY = startY - level[sub].getY();
		int finalY = endY - level[sub].getY();

		if (beginY < 0) beginY = 0;
		if (finalY > level[sub].getHeight()) finalY = level[sub].getHeight();

		int beginX = startX - level[sub].getX();
		int finalX = endX - level[sub].getX();

		if (beginX < 0) beginX = 0;
		if (finalX > level[sub].getWidth()) finalX = level[sub].getWidth();

		//сама отрисовка блоков, ради которой и был весь этот ужас сверху. Все это ради того, чтобы цикл не отрабатывал лишние итерации, тем самым загружая процессор
		for(int i = beginY; i < finalY; i++)
		{
			for (int j = beginX; j < finalX; j++)
			{
				level[sub].getMap()[i][j]->draw(win);
			}
		}
		//отрисовка сущностей
		for (int k = 0; k < level[sub].getEntities().size(); k++)
		{
				level[sub].getEntities()[k]->draw(win);
				DebugInformation::getInstance().renderedEntitiesCounter++;
		}

	}
}
void Level::update(sf::FloatRect viewRect)
{
	for (int sub = 0; sub < level.size(); sub++) //проход по вектору подуровней уровня
	{
		for (int k = 0; k < level[sub].getEntities().size(); k++)
		{
			if(level[sub].getEntities()[k]->getRect().intersects(viewRect)) //если сущность в поле зрения, то обновляю ее
			{
				DebugInformation::getInstance().updatedEntitiesCounter++;
				level[sub].getEntities()[k]->update();
			}
			else if(!level[sub].getEntities()[k]->isIndependent()) //удаляю несамостоятельные сущности, вылетевшие за пределы поля зрения
			{
				Content * ptr = level[sub].getEntities()[k];
				level[sub].getEntities().erase(level[sub].getEntityIterator(level[sub].getEntities()[k]));
				delete ptr;
			}
		}
	}
}
bool Level::isGameOver()
{
	return dynamic_cast<Player*>(player)->isGameOver();
}
bool Level::isLevelPassed()
{
	return dynamic_cast<Player*>(player)->isLevelPassed();
}
Level::~Level()
{
}
