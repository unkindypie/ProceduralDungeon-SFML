#pragma once
#include "ResourceManager.h"

struct keyreversecompare {
	bool operator() (const float& lhs, const float& rhs) const
	{
		return lhs > rhs;
	}
};

class Background
{
	sf::RenderTexture background;

	map<string, sf::Sprite>::iterator bgsprite;
	map<string, sf::Sprite>::iterator chain;
	multimap<float, map<string, sf::Sprite>::iterator, keyreversecompare> backgroundObjects;
	
	float height, width;
	int spriteWidth;
	int spriteHeight;
	float x, y;
public:
	Background(float width, float height, ResourceManager & rm);
	void draw(sf::RenderTarget & win, sf::FloatRect viewRect);
	void update(sf::FloatRect viewRect);
	~Background();
};

