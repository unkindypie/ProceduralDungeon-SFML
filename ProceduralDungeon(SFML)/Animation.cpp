#include "Animation.h"



Animation::Animation()
{
	currentFrame = 0;
	angle = 0;
}
void Animation::addFrame(ResourceManager & rm, string path, sf::IntRect rect)
{
	frames.push_back(rm.loadSprite(path, rect));//пропускаю картинку через ResourceManager, он проверяет есть ли она, если есть то дает итератор на нее, если нет то открывает и тоже дает итератор
	(*frames.back()).second.setOrigin(rect.width / 2, rect.height / 2); //ставлю центр, относительно которого берутся координаты в центер спрайта
}
map<string, sf::Sprite>::iterator & Animation::getCurrrentFrame()
{
	(*frames[int(currentFrame)]).second.setRotation(angle);//меняю угол спрайта соответсвенно углу анимации и возвращаю кадр
	return frames[int(currentFrame)]; 
}
void Animation::setAngle(int anlge)
{
	this->angle = anlge;
}
void Animation::tick()
{
	currentFrame += speed;//двигаю текущий кадр 
	if (currentFrame >= frames.size())  //в случае, если происходит выход за размер массива, то возвращаюсь в начало.(анимации цикличны)
	{
		currentFrame = 0;
	}
}
Animation::~Animation()
{
}
