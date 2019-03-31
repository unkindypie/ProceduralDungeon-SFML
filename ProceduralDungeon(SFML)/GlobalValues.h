#pragma once
class GlobalValues //класс, хран€щий глобальные статические переменные, доступ к которым осуществл€етс€ с помощью статических методов. ѕеременные читаютс€ из файла config.cfg
{
private:
	static int windowWidth;
	static int windowHeight;
	static int fpsLimit;
public:
	GlobalValues();
	static int getWindowWidth();
	static int getWindowHeight();
	static int getFpsLimit();
	~GlobalValues();
};
int GlobalValues::windowWidth = 1280;
int GlobalValues::windowHeight = 720;
int GlobalValues::fpsLimit = 60;


