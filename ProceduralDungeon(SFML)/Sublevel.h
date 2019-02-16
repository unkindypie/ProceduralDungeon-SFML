#pragma once
#include <vector>
#include "Block.h"

const size_t MIN_RAND_SIZE = 10; //8 минимальный размер подуровня
const size_t MAX_RAND_SIZE = 20; //20 максимальный размер подуровня
const size_t MAX_RAND_LOOP_COUNT = 40; //максимальное количество итераций цикла генерации размеров подуровня

extern int randomNumber(int minNum, int maxNum);

enum LevelGenerationState  //перечисление, отвечающее за попадание в ситуацию бесконечного цикла в конструкторах подуровней. Если такое случается, то весь уровень будет пересоздан заново.
{
	normal, restart
};
enum direction //перечисление позиций отверстия в подуровне
{
	left_, right_, top, down
};
enum HoleDestenation //перечисление для выбора назначения отвертвия. В одном случае оно сможет принимать координаты 0-hight или 0-width в другом нет
{
	x_sided, y_sided
};
enum holeMode //перечисление для определения работы конструктора. Либо сделать вход, либо сделать выход
{
	enter, exit_//на exit без _ ругалось
};
enum SublevelFillingType //перечисление типов наполнения подуровней
{
	first, last, clean, guntrapped_vertical, guntrapped_horizontal, razer 
};
class Sublevel
{
private:
	size_t x, y; //координаты подуровня в уровне
	size_t height, width; //высота и ширины подуровня

	int enterPosX = -1; //координаты точек входа и выхода
	int enterPosY = -1; // -1 взята как координата, которой не может быть на карте. Дальше это нужно в алгоритме генерации проходов
	int exitPosX = -1;
	int exitPosY = -1;
	sf::FloatRect exitRect; //FloatRect - класс прямоугольника, хранит свои координаты. Конкретно эти два я использую для обработки выхода и входа из подуровня
	sf::FloatRect enterRect;
	SublevelFillingType fillingType;//тип наполнения подуровня
	vector<vector<Content*>> map;//двумерный массив, хрянищий все блоки подуровня, представляет собой полиморфный кластер. Вот такие умные слова я знаю.
	//функция с кучей параметров, необходимоя для процедурной генерации координат проходов подуровня
	//ResourceManager *& rm;
	void generateEnterExit(int & coordX, int & coordY, size_t width, size_t height, direction holePosition); //функция генерации координат входа или выхода, удолетворяющих размерам подуровня
	bool angle = 0;
	
public:
	static size_t X_SIZE;
	static size_t Y_SIZE;
	Sublevel * next = NULL;
	Sublevel * prev = NULL;
	Sublevel();
	~Sublevel();
	//произвольная ширина
	Sublevel(size_t x, size_t y, int lastWidth, size_t holeCoordX, size_t holeCoordY, bool holeType, LevelGenerationState & gState, HoleDestenation holeDestenation, ResourceManager & rm); //конструктор подуровня с произвольной высотой
	//конструкторы с предустановленными координатами входа/выхода, произвольными высотой и шириной
	Sublevel(size_t x, size_t y, size_t holeCoordX, size_t holeCoordY, bool holeTyp, LevelGenerationState & gStatee, ResourceManager & rm); //конструктор для создания подуровня с отверствием с одной стороны и произвольными размерами(holeType = 0 - вход, 1 - выход)
	//конструкторы с произвольными координатами входа/выхода, шириной и высотой.
	Sublevel(size_t x, size_t y, direction holePosition, holeMode mode, LevelGenerationState & gState, ResourceManager & rm); //конструктор подуровня с произвольной координатой отверстия или отверстий(зависит от mode)
	vector<vector<Content*>> & getMap();
	void addExit(direction holePosition, ResourceManager & rm); //функция для создания выхода в уже созданном подуровне
	void addEnter(direction holePosition, ResourceManager & rm);
	//get методы
	void getExitGlobalCoords(float & x, float & y); //функция для получения глобальных координат выхода(в классе хранятся координаты относительно начала)
	void getEnterGlobalCoords(float & x, float & y); //функция для получения глобальных координат выхода(в классе хранятся координаты относительно начала)
	vector<Content*>::iterator getContentIterator(Content * cont); //возвращает итератор на элемент в векторе. Нужен для поиска и удаления элемента во время вызова из самого элемента
	void addContent(Content * c); //добавление элемента в вектор подуровня(в конец)
	void makeItAngle();
	bool isAngle();
	void fill(SublevelFillingType ft, ResourceManager & rm);
	size_t getX();
	size_t getY();
	sf::FloatRect getExitRect();
	sf::FloatRect getEnterRect();
	size_t getHeight();
	size_t getWidth();
	size_t getEnterPosX();
	size_t getEnterPosY();
	size_t getExitPosX();
	size_t getExitPosY();
	void addPlayerToEnter(ResourceManager & rm);
	//Sublevel & operator =(const Sublevel & sub);
};
size_t Sublevel::X_SIZE;
size_t Sublevel::Y_SIZE;