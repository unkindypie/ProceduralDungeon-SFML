#include "Entity.h"
#include "Player.h"
#include <string>


void Entity::move(float dirX, float dirY, float elapsedTime)
{
	elapsedTime *= speed;
	//-------обработка выхода из подуровня-------------
	x += dirX * elapsedTime; //сначала иду, потом проверяю столкновения(для выхода)
	y += dirY * elapsedTime;
	updateRect(); //обновляю прямоугольник спрайта, поскольку координаты изменились

	if (rect.intersects(current_sublevel->getExitRect()) && isDirectedToHole(dirX, dirY, exit_)) //обрабатываю выход из подуровня(проверяю, пересекает ли сущность прямоугольник выхода и двигается ли в сторону этого выхода)
	{
		float newXCord, newYCord;
		current_sublevel->next->getEnterGlobalCoords(newXCord, newYCord); //получаю координаты входа со следующего подуровня
		x = newXCord + (COMMON_SPRITE_SIZE + 2) / 2; //получаю центр(координаты берутся с левого верхнего угла)
		y = newYCord + (COMMON_SPRITE_SIZE + 2) / 2;
		updateRect();//обновляю прямоугольник игрока соответсвенно новым координатам
		current_sublevel->getMap()[current_sublevel->getHeight() - 1].erase(current_sublevel->getContentIterator(this)); // Я ПОФИКСИЛ ТОТ БАГ СО СКОРОСТЬЮ!!!!! Фишка в том,
		//что он обновлялся по нескольку раз, +1 при каждом переходе, потому что я не удалял указатель на игрока из старого вектора
		current_sublevel->next->getMap()[current_sublevel->next->getHeight() - 1].push_back(std::move(this)); //перемещаю сущность в следующий подуровень
		current_sublevel = current_sublevel->next;//теперь текущий подуровень стает следующим для сущности
		return;
	}
	else if(rect.intersects(current_sublevel->getEnterRect()) && isDirectedToHole(dirX, dirY, enter))//вход в подуровень
	{
		float newXCord, newYCord;
		current_sublevel->prev->getExitGlobalCoords(newXCord, newYCord);
		x = newXCord + (COMMON_SPRITE_SIZE + 2) / 2;
		y = newYCord + (COMMON_SPRITE_SIZE + 2) / 2;
		updateRect();
		current_sublevel->getMap()[current_sublevel->getHeight() - 1].erase(current_sublevel->getContentIterator(this));//фикс бага со скоростью
		current_sublevel->prev->getMap()[current_sublevel->prev->getHeight() - 1].push_back(std::move(this));
		current_sublevel = current_sublevel->prev;
		return;
	}
	else//в случае, если персонаж не находится в координатах выхода, то возвращаюсь обратно
	{
		x -= dirX * elapsedTime;
		y -= dirY * elapsedTime;
		updateRect();
	}
	//-------передвижение по подуровню--------------
	bool collide = 0;
	float prevx = x;
	float prevy = y;
	x += dirX * elapsedTime; //сначала иду, потом проверяю столкновения. Если они есть, то иду обратно
	y += dirY * elapsedTime;
	updateRect();

	//отнимаю от координаты персонажа прямоугольника персонажа относительно начала координату начала подуровня деля на размер спрайта в пикселях получая координату блока в массиве
	for (int i = (rect.top - current_sublevel->getY()*COMMON_SPRITE_SIZE) / COMMON_SPRITE_SIZE; i < (rect.top - current_sublevel->getY()*COMMON_SPRITE_SIZE + rect.height) / COMMON_SPRITE_SIZE; i++)
	{
		for (int j = (rect.left - current_sublevel->getX()*COMMON_SPRITE_SIZE) / COMMON_SPRITE_SIZE; j < ((rect.left - current_sublevel->getX()*COMMON_SPRITE_SIZE) + rect.width) / COMMON_SPRITE_SIZE; j++)
		{
			if(i < 0 || i > current_sublevel->getHeight()-1 || j < 0 || j > current_sublevel->getWidth() - 1)//защита от выхода за массив
			{
				x -= dirX * elapsedTime;//иду обратно
				y -= dirY * elapsedTime;
				updateRect();//обновляю прямоугольник спрайта
				return;
			}
			if (current_sublevel->getMap()[i][j]->getRect().intersects(rect) && current_sublevel->getMap()[i][j]->isCollides())//проверка на пересечение между прямоугольниками спрайтов
			{//проверяю, не пересекает ли один из прямоугольников спрайтов подуровня прямоугольник моего спрайта, и если да и тот элемент имеет коллизии, то иду обратно
				collide = 1;
			}
		}
	}
	if (collide)  //поскольку в тот if может зайти много раз, чтобы зря не обновлять прямоугольник спрайта 100500 раз вынес в отдельный if
	{
		x -= dirX * elapsedTime;//иду обратно
		y -= dirY * elapsedTime;
		updateRect();//обновляю прямоугольник спрайта
	}
	//cout << "dif X:" << x - prevx << " dif Y:" << y - prevy << endl;
}
void Entity::hit(Entity * en)
{
	if(en->isHitable())
	{
		en->decreaseHealth(damage);
	}
}
bool Entity::isDirectedToHole(float dirX, float dirY, holeMode hole) //функция, провериющая двигается ли сущность в сторону прохода
{
	float holeX, holeY;
	if(hole == enter)
	{
		holeX = current_sublevel->getEnterPosX();
		holeY = current_sublevel->getEnterPosY();
	}
	else
	{
		holeX = current_sublevel->getExitPosX();
		holeY = current_sublevel->getExitPosY();
	}
	if (dirX == 1 && current_sublevel->getWidth()-1 == holeX) return true;
	if (dirX == -1 && holeX == 0) return true;
	if (dirY == 1 && holeY == current_sublevel->getHeight()-1) return true;
	if (dirY == -1 && holeY == 0) return true;

	return false;
}
void Entity::decreaseHealth(float value)
{
	health -= value;

	if (health <= 0) {
		current_sublevel->getMap()[current_sublevel->getHeight() - 1].erase(current_sublevel->getContentIterator(this));
		//delete this;
	}

}
bool Entity::damageDealing()
{
	for (int i = current_sublevel->getWidth() - 1; i < current_sublevel->getMap()[current_sublevel->getHeight() - 1].size(); i++)
	{
		if (current_sublevel->getMap()[current_sublevel->getHeight() - 1][i]->getRect().intersects(rect) && current_sublevel->getMap()[current_sublevel->getHeight() - 1][i]->isHitable() && current_sublevel->getMap()[current_sublevel->getHeight() - 1][i] != this)
		{
			this->hit(dynamic_cast<Entity*>(current_sublevel->getMap()[current_sublevel->getHeight() - 1][i])); //при столкновении с другой сущностью наношу ей урон и удаляю пулю
			
			return true; 
		}
	}
	return false;
}
Sublevel * Entity::getCurrentSublevel()
{
	return current_sublevel;
}
Entity::Entity()
{
	hitable = true;
}

void Entity::updateRect()
{
	(*sprite_iterator).second.setPosition(x, y);
	rect = (*sprite_iterator).second.getGlobalBounds();
	rect.height--;
	rect.width--;
	rect.left--;
	rect.top--;
}
Entity::~Entity()
{
}
double Entity::getSpeed()
{
	return speed;
}