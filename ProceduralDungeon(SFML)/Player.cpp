#include "Player.h"
#include <windows.h>
//Player::Player()
//{
//	health = 5;
//	//collides = 0;
//}
Player::Player(float x, float y, Sublevel * sub, ResourceManager & rm1) /*: Player()*/ : rm(rm1)
{
	dirX = 0;
	dirY = -1;
	health = 5;
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

	//int localX = x - current_sublevel->getX();
	//int localY = y - current_sublevel->getY();
	//if (localX + dirX >= 0 && localX + dirX < current_sublevel->getWidth() &&
	//	localY + dirY >= 0 && localY + dirY < current_sublevel->getHeight())//если данный элемент массива может существовать
	//{
	//	if (!current_sublevel->getMap()[localY + dirY][localX + dirX]->isCollides()) //и не имеет колизий
	//	{
	//		current_sublevel->getMap()[localY + dirY][localX + dirX] = new Bullet(x + dirX, y + dirY, dirX, dirY, current_sublevel);
	//	}
	//}
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
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(currentTime >= shootingCooldown)
		{
			shoot();
			currentTime = 0;
		}
	}


	//if(GetAsyncKeyState(VK_SPACE))
	//{
	//	shoot();
	//}
}
void Player::update(float elapsedTime)
{
	movement(elapsedTime);
	//draw();
	currentTime += elapsedTime;
}
void Player::draw(sf::RenderWindow & win)
{
	sprite_iterator->second.setPosition(x, y);
	win.draw(sprite_iterator->second);
	//sprite_iterator->second.setPosition(0, 0);

}
Player::~Player()
{
}
