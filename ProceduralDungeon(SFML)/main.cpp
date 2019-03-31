#include "Level.h"
#include "GameInterface.h"

int main()
{
	srand(time(NULL));
	GlobalValues gl;
	sf::RenderWindow window(sf::VideoMode(GlobalValues::getWindowWidth(), GlobalValues::getWindowHeight()), L"TODO: Придумать игре название"); //класс окна, в этой строчке я указываю его разрешение и название
	sf::Clock updateClock; //класс счетчик времени, позволяет засекать и сбрасывать насчитанное время.
	Level level(70/*WINDOW_WIDTH / COMMON_SPRITE_SIZE*/, 70/*WINDOW_HEIGHT / COMMON_SPRITE_SIZE*/); //создаю уровень
	GameCamera cam(level.player, window); //игровая камера будет следить за игркоом
	GameInterface interf(&level, cam); //интерфейс будет выводить жизни игрока относительно координат камеры
	updateClock.restart();

	float frames = GlobalValues::getFpsLimit();
	float frameOffset = 1000 / frames;
	float nextUpdate = updateClock.getElapsedTime().asMilliseconds();//это количество обновлений игрового цикла в герцах
	float sleepTime = 0;
	sf::Event event; //sfml класс событие, позволяет обрабатывать много чего, в данном случае я использую его для обработки закрытия окна
	float endCounter = 0;
	while (window.isOpen())
	{
		while (window.pollEvent(event)) //обрабатываю закрытие окна
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();//чищу окно от прошлого кадра

		level.update(sf::FloatRect{ window.getView().getCenter().x - window.getSize().x / 2, window.getView().getCenter().y - window.getSize().y / 2, (float)window.getSize().x, (float)window.getSize().y }); //обновление 
		cam.update(1);
		interf.update(cam.getX(), cam.getY());
		
		level.draw(window); //отрисовка
		interf.draw(window);
		window.display();
		if (level.isGameOver())
		{
			cam.deathcam();
			interf.gameover();
			endCounter++;
			if (endCounter > 200)
			{
				break;
			}
		}
		if (level.isLevelPassed())
		{
			cam.deathcam();
			interf.gamepassed();
			endCounter++;
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