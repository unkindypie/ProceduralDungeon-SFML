#pragma once
#include "ResourceManager.h"
#include <vector>
class Animation //класс анимации представляет собой вектор итераторов на спрайты, хранящиеся в ResourceManager
{
private:
	vector<map<string, sf::Sprite>::iterator> frames;//вектор кадров анимации
	float currentFrame;//текущий кадр, который должен быть отрисован
	int angle; //угол спрайта
	float speed = 0.1;
public:
	Animation();
	void addFrame(ResourceManager & rm, string path, sf::IntRect rect); //добавление кадра в нимацию
	map<string, sf::Sprite>::iterator & getCurrrentFrame(); //получение текущего кадра
	void tick();//тик анимации. Необходим для прокрутки анимации(прохода по вектору)
	void setAngle(int anlge);
	~Animation();
};

