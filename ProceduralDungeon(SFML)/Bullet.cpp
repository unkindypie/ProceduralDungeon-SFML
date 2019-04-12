#include "Bullet.h"



Bullet::Bullet()
{
}
Bullet::Bullet(float x, float y, int dirX, int dirY, Sublevel * current_sublevel, ResourceManager & rm)
{
	this->x = x;
	this->y = y;
	damage = 1;
	speed = 0.1 * speedMultiplier;
	hitable = false;
	shader = "lightning";
	independent = false; //пуля не самостаятельная. При выходе за экран она исчезнет
	//sprite_iterator = rm.loadSprite("images/fire1.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
	am.addAnimation("fly");
	am.addFrame("fly", rm, "images/fire1.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	am.addFrame("fly", rm, "images/fire2.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	am.addFrame("fly", rm, "images/fire3.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	am.addFrame("fly", rm, "images/fire4.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	am.addFrame("fly", rm, "images/fire5.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	am.addFrame("fly", rm, "images/fire6.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
	am.addFrame("fly", rm, "images/fire7.png", sf::IntRect(0, 0, pxSizeX, pxSizeY));
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
	updateRect();
}
void Bullet::fly()
{
	move(dirX, dirY);
}

void Bullet::hitDetection()
{
	bool collide = 0;

	x += dirX * speed; //сначала иду, потом проверяю столкновения. Если они есть, то иду обратно
	y += dirY * speed;
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
		}
	}
	if(damageDealing()) //если пуля сталкивается с другой сущностью, то наношу ей урон(damageDealing), эта функция вовзращает true в таком случае и я удаляю пулю
	{
		current_sublevel->getEntities().erase(current_sublevel->getEntityIterator(this));
		delete this;
		return;
	}
	
	if (x - COMMON_SPRITE_SIZE / 2 - current_sublevel->getX() * COMMON_SPRITE_SIZE + dirX * speed < 0 && x + COMMON_SPRITE_SIZE / 2 - current_sublevel->getX() * COMMON_SPRITE_SIZE + dirX * speed > current_sublevel->getWidth() * COMMON_SPRITE_SIZE &&
		y - COMMON_SPRITE_SIZE / 2 - current_sublevel->getY() * COMMON_SPRITE_SIZE + dirY * speed < 0 && y + COMMON_SPRITE_SIZE / 2 - current_sublevel->getY() * COMMON_SPRITE_SIZE + dirY * speed > current_sublevel->getHeight() * COMMON_SPRITE_SIZE)
	{
		collide = 1;
	}
	if (collide)  //поскольку в тот if может зайти много раз, чтобы зря не обновлять прямоугольник спрайта 100500 раз вынес в отдельный if
	{
		current_sublevel->getEntities().erase(current_sublevel->getEntityIterator(this));
		delete this;
	}
}
void Bullet::update()
{
	sprite_iterator = am.getCurrentFrame();
	am.tick();
	fly();
	hitDetection();

}
void Bullet::draw(sf::RenderTarget & win)
{
	sprite_iterator = am.getCurrentFrame();
	sprite_iterator->second.setPosition(x, y);
	win.draw(sprite_iterator->second);
}
Bullet::~Bullet()
{
}
