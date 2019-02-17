#include "Level.h"
#include "GameInterface.h"
int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;


int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), L"TODO: Придумать игре название"); //класс окна, в этой строчке я указываю его разрешение и название
	sf::Clock updateClock; //класс счетчик времени, позволяет засекать и сбрасывать насчитанное время.
	Level level(70/*WINDOW_WIDTH / COMMON_SPRITE_SIZE*/, 70/*WINDOW_HEIGHT / COMMON_SPRITE_SIZE*/); //создаю уровень
	GameCamera cam(level.player, window); //игровая камера будет следить за игркоом
	GameInterface interf(level.getResourceManager(), cam, WINDOW_HEIGHT, WINDOW_WIDTH, level.getPlayerTries()); //интерфейс будет выводить жизни игрока относительно координат камеры

	updateClock.restart();

	float elapsedTime;// здесь хранится прошеднее время
	float frames = 30;
	float frameOffset = 1000 / frames;
	float nextUpdate = updateClock.getElapsedTime().asMilliseconds();//это количество обновлений игрового цикла в герцах
	float sleepTime = 0;
	sf::Event event; //sfml класс событие, позволяет обрабатывать много чего, в данном случае я использую его для обработки закрытия окна
	float endCounter = 0;
	elapsedTime = 1;
	while (window.isOpen())
	{

		while (window.pollEvent(event)) //обрабатываю закрытие окна
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();//чищу окно от прошлого кадра

		level.update(elapsedTime); //обновление 
		cam.update(elapsedTime);
		interf.update(cam, level.getPlayerTries());


		level.draw(window); //отрисовка
		interf.draw(window);
		window.display();
		if (level.isGameOver())
		{
			cam.deathcam();
			interf.gameover();
			endCounter += elapsedTime;
			if (endCounter > 200)
			{
				break;
			}
		}
		if (level.isLevelPassed())
		{
			cam.deathcam();
			interf.gamepassed();
			endCounter += elapsedTime;
			if (endCounter > 200)
			{
				break;
			}
		}
		nextUpdate += frameOffset;
		sleepTime = nextUpdate - updateClock.getElapsedTime().asMilliseconds();
		if(sleepTime >= 0)
		{
			sf::sleep(sf::milliseconds(sleepTime));
		}
	}
	return 0;
}