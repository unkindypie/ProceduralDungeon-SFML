#include "FPSMonitor.h"
#include <sstream>;


FPSMonitor::FPSMonitor(map<string, sf::Font>::iterator font_iterator)
{
	text.setFont((*font_iterator).second);
	text.setString("FPS:");
	fps = 0;
	text.setScale(0.5, 0.5);
	offsetX = -(GlobalValues::getWindowWidth() / 2 ) + 20;
	offsetY = -(GlobalValues::getWindowHeight() / 2) + 20;
}

void FPSMonitor::update(int newX, int newY)
{
	
	x = newX + offsetX;
	y = newY + offsetY;
	if (visible) {
		fps++;
		if (clock.getElapsedTime().asMilliseconds() >= 1000)
		{
			clock.restart();
			stringstream ss;
			ss << "FPS: " << fps;
			text.setString(ss.str());
			fps = 0;
		}
	}
}


FPSMonitor::~FPSMonitor()
{
}
