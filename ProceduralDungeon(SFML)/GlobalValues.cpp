#include "GlobalValues.h"
#include <fstream>
#include <string>

using namespace std;

GlobalValues::GlobalValues()
{
	ifstream ifs;
	ifs.open("config.cfg");
	if(!ifs.is_open()) //если файла нет, создаю
	{
		ofstream ofs;
		ofs.open("config.cfg");
		ofs << "WindowWidth: 1280\nWindowHeight: 720";
		windowWidth = 1280;
		windowHeight = 720;
	}
	else //если есть, то читаю и сохран€ю в пол€ класса
	{
		string buf;
		int pos = 0;
		while (getline(ifs, buf))
		{
			switch (pos)
			{
			case 0:
				windowWidth = atoi(buf.c_str() + 13);
				break;
			case 1:
				windowHeight = atoi(buf.c_str() + 14);
				break;
			default:
				break;
			}
			pos++;
		}
	}
}

int GlobalValues::getWindowWidth()
{
	return windowWidth;
}

int GlobalValues::getWindowHeight()
{
	return windowHeight;
}


GlobalValues::~GlobalValues()
{
}
