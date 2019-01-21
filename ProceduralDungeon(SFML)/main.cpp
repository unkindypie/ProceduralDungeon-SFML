#include "Level.h"
#include "GameInterface.h"

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;


int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dungeon"); //класс окна, в этой строчке я указываю его разрешение и название
	Level level(WINDOW_WIDTH / COMMON_SPRITE_SIZE, WINDOW_HEIGHT / COMMON_SPRITE_SIZE); //создаю уровень
	GameCamera cam(level.player, window); //игровая камера будет следить за игркоом
	GameInterface interf(level.getResourceManager(), cam, WINDOW_HEIGHT, WINDOW_WIDTH, level.getPlayerTries()); //интерфейс будет выводить жизни игрока относительно координат камеры

	sf::Clock updateClock; //класс счетчик времени, позволяет засекать и сбрасывать насчитанное время.

	float elapsedTime;// здесь хранится прошеднее время
	float nextUpdate = 1.f/30.f; //это количество обновлений игрового цикла в герцах
	sf::Event event; //sfml класс событие, позволяет обрабатывать много чего, в данном случае я использую его для обработки закрытия окна
	while (window.isOpen())
	{
		elapsedTime = updateClock.getElapsedTime().asMicroseconds() / 800;//получаю насчи
		//elapsedTime = updateClock.getElapsedTime().asSeconds();
		if(elapsedTime >= nextUpdate)
		{
			
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();

			level.update(elapsedTime);
			cam.update(elapsedTime);
			interf.update(cam, level.getPlayerTries());

			level.draw(window);
			interf.draw(window);
			window.display();
			
			updateClock.restart();
		}
	
	}
	return 0;
}