#pragma once
#include "UIText.h"
class FPSMonitor :
	public UIText
{
private:
	sf::Clock clock;
	int fps;
public:
	FPSMonitor(map<string, sf::Font>::iterator font_iterator);
	void update(int newX, int newY);
	~FPSMonitor();
};

