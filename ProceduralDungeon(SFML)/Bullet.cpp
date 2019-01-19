#include "Bullet.h"



Bullet::Bullet()
{
}
Bullet::Bullet(float x, float y, int dirX, int dirY, Sublevel * current_sublevel, ResourceManager & rm)
{
	this->x = x;
	this->y = y;
	damage = 1;
	speed = 0.1;
	health = 1000;
	//sprite_iterator = rm.loadSprite("images/fire1.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addAnimation("fly");
	am.addFrame("fly", rm, "images/fire1.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addFrame("fly", rm, "images/fire2.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addFrame("fly", rm, "images/fire3.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addFrame("fly", rm, "images/fire4.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addFrame("fly", rm, "images/fire5.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addFrame("fly", rm, "images/fire6.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addFrame("fly", rm, "images/fire7.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.setCurrentAnimation("fly");
	if(dirX == 0 && dirY == -1)
	{
		am.setAngle(180);
	}
	if (dirX == 0 && dirY == 1)
	{
		am.setAngle(0);
	}
	if (dirX == 1 && dirY == 0)
	{
		am.setAngle(-90);
	}
	if (dirX == -1 && dirY == 0)
	{
		am.setAngle(90);
	}
	sprite_iterator = am.getCurrentFrame();
	this->current_sublevel = current_sublevel;
	this->dirX = dirX;
	this->dirY = dirY;
}
void Bullet::fly(float elapsedTime)
{
	move(dirX, dirY, elapsedTime);
}

void Bullet::hitDetection(float elapsedTime)
{
	elapsedTime *= speed;
	bool collide = 0;
	elapsedTime *= speed;

	x += dirX * elapsedTime; //сначала иду, потом проверяю столкновения. Если они есть, то иду обратно
	y += dirY * elapsedTime;
	updateRect();
	//отнимаю от координаты персонажа прямоугольника персонажа относительно начала координату начала подуровня деля на размер спрайта в пикселях получая координату блока в массиве
	for (int i = (rect.top - current_sublevel->getY()*COMMON_SPRITE_SIZE) / COMMON_SPRITE_SIZE; i < (rect.top - current_sublevel->getY()*COMMON_SPRITE_SIZE + rect.height) / COMMON_SPRITE_SIZE; i++)
	{
		for (int j = (rect.left - current_sublevel->getX()*COMMON_SPRITE_SIZE) / COMMON_SPRITE_SIZE; j < ((rect.left - current_sublevel->getX()*COMMON_SPRITE_SIZE) + rect.width) / COMMON_SPRITE_SIZE; j++)
		{
			if (current_sublevel->getMap()[i][j]->getRect().intersects(rect) && current_sublevel->getMap()[i][j]->isCollides())//проверка на пересечение между прямоугольниками спрайтов
			{//проверяю, не пересекает ли один из прямоугольников спрайтов подуровня прямоугольник моего спрайта, и если да и тот элемент имеет коллизии, то иду обратно
				collide = 1;
			}
			if (current_sublevel->getMap()[i][j]->getRect().intersects(rect) && current_sublevel->getMap()[i][j]->isHitable())
			{
				this->hit(dynamic_cast<Entity*>(current_sublevel->getMap()[i][j])); //при столкновении с другой сущностью наношу ей урон и удаляю пулю
				current_sublevel->getMap()[current_sublevel->getHeight() - 1].erase(current_sublevel->getContentIterator(this));
				delete this;
			}
		}
	}
	if (x - COMMON_SPRITE_SIZE / 2 - current_sublevel->getX() * COMMON_SPRITE_SIZE + dirX * elapsedTime < 0 && x + COMMON_SPRITE_SIZE / 2 - current_sublevel->getX() * COMMON_SPRITE_SIZE + dirX * elapsedTime > current_sublevel->getWidth() * COMMON_SPRITE_SIZE &&
		y - COMMON_SPRITE_SIZE / 2 - current_sublevel->getY() * COMMON_SPRITE_SIZE + dirY * elapsedTime < 0 && y + COMMON_SPRITE_SIZE / 2 - current_sublevel->getY() * COMMON_SPRITE_SIZE + dirY * elapsedTime > current_sublevel->getHeight() * COMMON_SPRITE_SIZE)
	{
		collide = 1;
	}
	if (collide)  //поскольку в тот if может зайти много раз, чтобы зря не обновлять прямоугольник спрайта 100500 раз вынес в отдельный if
	{
		current_sublevel->getMap()[current_sublevel->getHeight() - 1].erase(current_sublevel->getContentIterator(this));
		delete this;
	}
}
void Bullet::update(float elapsedTime)
{
	sprite_iterator = am.getCurrentFrame();
	am.tick(elapsedTime);
	fly(elapsedTime);
	hitDetection(elapsedTime);

}
void Bullet::draw(sf::RenderWindow & win)
{
	sprite_iterator = am.getCurrentFrame();
	sprite_iterator->second.setPosition(x, y);
	win.draw(sprite_iterator->second);
}
Bullet::~Bullet()
{
}
