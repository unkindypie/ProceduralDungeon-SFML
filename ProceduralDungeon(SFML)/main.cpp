#include "Level.h"
#include "GameInterface.h"

int WINDOW_WIDTH = 1920;
int WINDOW_HEIGHT = 1080;


int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dungeon");
	Level level(WINDOW_WIDTH / COMMON_SPRITE_SIZE, WINDOW_HEIGHT / COMMON_SPRITE_SIZE);
	GameCamera cam(level.player, window);
	GameInterface interf(level.getResourceManager(), cam, WINDOW_HEIGHT, WINDOW_WIDTH, level.getPlayerTries());

	sf::Clock updateClock; 

	float elapsedTime;


	while (window.isOpen())
	{
		
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		elapsedTime = updateClock.getElapsedTime().asMicroseconds() / 800;
		if (elapsedTime > 10) {
			elapsedTime = 10;
		}
		window.clear();

		level.update(elapsedTime);
		updateClock.restart();
		cam.update(elapsedTime);
		interf.update(cam, level.getPlayerTries());

		level.draw(window);
		interf.draw(window);
		window.display();
		
	}
	return 0;
}