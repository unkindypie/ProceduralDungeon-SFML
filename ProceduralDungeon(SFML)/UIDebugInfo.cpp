#include "UIDebugInfo.h"
#include <sstream>


UIDebugInfo::UIDebugInfo(map<string, sf::Font>::iterator font_iterator)
{
	entitiesRendered = UIText("EntitiesRend: ", font_iterator, -(GlobalValues::getWindowWidth() / 2) + 20, -(GlobalValues::getWindowHeight() / 2) + 45);
	entitiesUpdated = UIText("EntitiesUpd: ", font_iterator, -(GlobalValues::getWindowWidth() / 2) + 20, -(GlobalValues::getWindowHeight() / 2) + 60);
	entitiesRendered.text.setScale(0.4, 0.4);
	entitiesUpdated.text.setScale(0.4, 0.4);
}

void UIDebugInfo::draw(sf::RenderWindow & win)
{
	if(visible)
	{
		stringstream ss;
		ss << "EntitiesRend: " << DebugInformation::getInstance().renderedEntitiesCounter;
		entitiesRendered.text.setString(ss.str());
		stringstream ss1;
		ss1 << "EntitiesUpd: " << DebugInformation::getInstance().updatedEntitiesCounter;
		entitiesUpdated.text.setString(ss1.str());

		entitiesRendered.draw(win);
		entitiesUpdated.draw(win);
	}
}

void UIDebugInfo::update(int newX, int newY)
{
	entitiesRendered.update(newX, newY);
	entitiesUpdated.update(newX, newY);
}

void UIDebugInfo::setVisibility(bool value)
{
	entitiesRendered.setVisibility(value);
	entitiesUpdated.setVisibility(value);
}




UIDebugInfo::~UIDebugInfo()
{
}
