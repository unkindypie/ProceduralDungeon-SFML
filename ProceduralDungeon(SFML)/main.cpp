#include "Level.h"
#include "GameInterface.h"

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;


int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dungeon");
	Level level(WINDOW_WIDTH / COMMON_SPRITE_SIZE, WINDOW_HEIGHT / COMMON_SPRITE_SIZE);
	GameCamera cam(level.player, window);
	GameInterface interf(level.getResourceManager(), cam, WINDOW_HEIGHT, WINDOW_WIDTH, level.getPlayerTries());

	sf::Clock updateClock; 

	float elapsedTime;
	float nextUpdate = 1.f/40.f;
	sf::Event event;
	while (window.isOpen())
	{
		elapsedTime = updateClock.getElapsedTime().asMicroseconds() / 800;
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