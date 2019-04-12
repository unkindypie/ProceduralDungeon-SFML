#include "Player.h"
#include <windows.h>
#include <iostream>

Player::Player(float x, float y, Sublevel * sub, ResourceManager & rm1) : rm(rm1)
{
	dirX = 0;
	dirY = -1;
	health = 1;
	tries = 10;
	speed = 0.3 * speedMultiplier;
	independent = true; //игрок самосто€тельный. ѕри выходе за пределы экрана он продолжит жить
	//pxSizeX = 64;
	//pxSizeY = 64;
	pxSizeX = 16;
	pxSizeY = 16;
	//currentTime = 0;
	//shootingCooldown = 300;
	current_sublevel = sub;
	this->x = sub->getX() * COMMON_SPRITE_SIZE + x;
	this->y = sub->getY() * COMMON_SPRITE_SIZE + y;
	this->rm = rm;
	//sprite_iterator = rm.loadSprite("images/player.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addAnimation("stand");
	am.addAnimation("walk");
	am.addFrame("stand", rm, "images/player1.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	am.addFrame("walk", rm, "images/player2.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	am.addFrame("walk", rm, "images/player3.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	/*am.addFrame("stand", rm, "images/newplayer.png", sf::IntRect(0, 0 * pxSizeX, pxSizeX, pxSizeY));

	am.addFrame("walk", rm, "images/newplayer.png", sf::IntRect(0, 0 * pxSizeX, pxSizeX, pxSizeY));
	am.addFrame("walk", rm, "images/newplayer.png", sf::IntRect(0, 1 * pxSizeX, pxSizeX, pxSizeY));
	am.addFrame("walk", rm, "images/newplayer.png", sf::IntRect(0, 2 * pxSizeX, pxSizeX, pxSizeY));
	am.addFrame("walk", rm, "images/newplayer.png", sf::IntRect(0, 3 * pxSizeX, pxSizeX, pxSizeY));
	am.addFrame("walk", rm, "images/newplayer.png", sf::IntRect(0, 4 * pxSizeX, pxSizeX, pxSizeY));
	am.addFrame("walk", rm, "images/newplayer.png", sf::IntRect(0, 5 * pxSizeX, pxSizeX, pxSizeY));*/

	am.setCurrentAnimation("stand");
	sprite_iterator = am.getCurrentFrame();
	(*sprite_iterator).second.setOrigin(pxSizeX / 2, pxSizeY / 2);
	updateRect();
}
ResourceManager & Player::getResourceManager()
{
	return rm;
}
void Player::shoot()
{
	current_sublevel->addEntity(new Bullet(x, y, dirX, dirY, current_sublevel, rm));
}
void Player::movement()
{
	am.setCurrentAnimation("stand");
	sprite_iterator = am.getCurrentFrame();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move(0, -1);
		dirX = 0;
		dirY = -1;
		am.setCurrentAnimation("walk");
		am.setAngle(0);
		sprite_iterator = am.getCurrentFrame();
		am.tick();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move(0, 1);
		dirX = 0;
		dirY = 1;
		am.setCurrentAnimation("walk");
		am.setAngle(180);
		sprite_iterator = am.getCurrentFrame();
		am.tick();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(1, 0);
		dirX = 1;
		dirY = 0;
		am.setCurrentAnimation("walk");
		am.setAngle(90);
		sprite_iterator = am.getCurrentFrame();
		am.tick();

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move(-1, 0);
		dirX = -1;
		dirY = 0;
		am.setCurrentAnimation("walk");
		am.setAngle(-90);
		sprite_iterator = am.getCurrentFrame();
		am.tick();
	}
	/*if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(currentTime >= shootingCooldown)
		{
			shoot();
			currentTime = 0;
		}
	}*/
}
void Player::decreaseHealth(float value)
{
	health -= value;

	if (health <= 0) {
		tries--;
		if(tries < 1)
		{
			gameOver = true;
		}
		else
		{
			health = 1;
			float newXCord, newYCord;
			current_sublevel->getEnterGlobalCoords(newXCord, newYCord);
			x = newXCord + (COMMON_SPRITE_SIZE + 2) / 2;
			y = newYCord + (COMMON_SPRITE_SIZE + 2) / 2;
			updateRect();
		}
	}

}
void Player::update()
{
	if (current_sublevel->next == NULL)
	{
		levelPassed = true;
	}
	if (health <= 0)
	{
		//delete this;
		return;
	}
	movement();
	
	//if(globalClock.getElapsedTime().asSeconds() >= 1) //причина бага ускорени€ находитс€ где-то здесь. — каждыи проходом через вход/выход количество обновлений возрастает в 2 раза от изначального(30)
	//{
	//	cout << plUpdates << endl;
	//	plUpdates = 0;
	//	globalClock.restart();
	//	return;
	//}
	//plUpdates++;
	//currentTime += elapsedTime;
}
void Player::draw(sf::RenderTarget & win)
{
	if(health > 0)
	{
		sprite_iterator->second.setPosition(x, y);
		win.draw(sprite_iterator->second);
	}
	
}
bool Player::isGameOver()
{
	return gameOver;
}
bool Player::isLevelPassed()
{
	//return false;
	return levelPassed;
}
int Player::getTries()
{
	return tries;
}

Player::~Player()
{
}
