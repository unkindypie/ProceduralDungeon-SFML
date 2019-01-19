//#include <SFML/Graphics.hpp>
#include "Level.h"
#include <SFML/System.hpp>
#include <iostream>
int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Dungeon");
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 1280, 720));
	Level level;
	sf::Clock updateClock; 
	float elapsedTime;
	size_t updates;
	float updateNext = updateClock.getElapsedTime().asMilliseconds();
	float updateTime;
	view.setCenter(level.player->getX(), level.player->getY());
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

		view.setCenter(level.player->getX(), level.player->getY());
		window.setView(view);
		
		level.draw(window);
		window.display();
		
	}
	return 0;
}