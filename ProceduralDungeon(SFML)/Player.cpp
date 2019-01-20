#include "Player.h"
#include <windows.h>
Player::Player(float x, float y, Sublevel * sub, ResourceManager & rm1) : rm(rm1)
{
	dirX = 0;
	dirY = -1;
	health = 1;
	tries = 10;
	speed = 0.1;
	currentTime = 0;
	shootingCooldown = 300;
	current_sublevel = sub;
	this->x = x;
	this->y = y;
	this->rm = rm;
	//sprite_iterator = rm.loadSprite("images/player.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addAnimation("stand");
	am.addAnimation("walk");
	am.addFrame("stand", rm, "images/player1.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addFrame("walk", rm, "images/player2.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addFrame("walk", rm, "images/player3.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.setCurrentAnimation("stand");
	sprite_iterator = am.getCurrentFrame();
	(*sprite_iterator).second.setOrigin(COMMON_SPRITE_SIZE / 2, COMMON_SPRITE_SIZE / 2);
	updateRect();
}
void Player::shoot()
{
	current_sublevel->addContent(new Bullet(x /*- (dirX * COMMON_SPRITE_SIZE)*/, y /*- (dirY * COMMON_SPRITE_SIZE)*/, dirX, dirY, current_sublevel, rm));
}
void Player::movement(float elapsedTime)
{
	am.setCurrentAnimation("stand");
	sprite_iterator = am.getCurrentFrame();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move(0, -1, elapsedTime);
		dirX = 0;
		dirY = -1;
		am.setCurrentAnimation("walk");
		am.setAngle(0);
		sprite_iterator = am.getCurrentFrame();
		am.tick(elapsedTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move(0, 1, elapsedTime);
		dirX = 0;
		dirY = 1;
		am.setCurrentAnimation("walk");
		am.setAngle(180);
		sprite_iterator = am.getCurrentFrame();
		am.tick(elapsedTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(1, 0, elapsedTime);
		dirX = 1;
		dirY = 0;
		am.setCurrentAnimation("walk");
		am.setAngle(90);
		sprite_iterator = am.getCurrentFrame();
		am.tick(elapsedTime);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move(-1, 0, elapsedTime);
		dirX = -1;
		dirY = 0;
		am.setCurrentAnimation("walk");
		am.setAngle(-90);
		sprite_iterator = am.getCurrentFrame();
		am.tick(elapsedTime);
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
			//gameover		
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
void Player::update(float elapsedTime)
{
	if(health <= 0)
	{
		//delete this;
		return;
	}
	movement(elapsedTime);
	currentTime += elapsedTime;
}
void Player::draw(sf::RenderWindow & win)
{
	if(health > 0)
	{
		sprite_iterator->second.setPosition(x, y);
		win.draw(sprite_iterator->second);
	}
	
}

int Player::getTries()
{
	return tries;
}

Player::~Player()
{
}
