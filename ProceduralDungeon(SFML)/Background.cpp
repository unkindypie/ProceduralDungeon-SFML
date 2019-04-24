#include "Background.h"
#include <iostream>

Background::Background(float width, float height, ResourceManager & rm)
{
	this->width = width;
	this->height = height;
	spriteHeight = 700;
	spriteWidth = 1500;
	x = 0;
	y = 0;
	bgsprite = rm.loadSprite("images/background.png", sf::IntRect(0, 0, spriteWidth, spriteHeight));
	(*bgsprite).second.setTextureRect(sf::IntRect(0, 0, GlobalValues::getWindowWidth() * 2, GlobalValues::getWindowHeight() * 2));
	backgroundObjects.emplace(3, rm.loadSprite("images/background.png", sf::IntRect(0, 0, spriteWidth, spriteHeight)));

	chain = rm.loadSprite("images/chain.png", sf::IntRect(0, 0, 156, 1600));
	sf::Texture chainTexture;
	chainTexture.loadFromFile("images/chain.png", sf::IntRect(0, 0, 156, 1600));
	chainTexture.create(GlobalValues::getWindowWidth() / 2, 1600);
	//chainTexture.setRepeated(true);
	//backgroundObjects.emplace(2.3, rm.downloadSprite("resizedChaing", sf::Sprite(chainTexture)));
	
	
	
}

void Background::draw(sf::RenderTarget & win, sf::FloatRect viewRect)
{
	
	for (multimap<float, map<string, sf::Sprite>::iterator>::iterator i = backgroundObjects.begin(); i != backgroundObjects.end(); i++)
	{
		win.draw((*(*i).second).second);
	}
}

void Background::update(sf::FloatRect viewRect)
{
	//(*bgsprite).second.setPosition(viewRect.left, viewRect.top);
	//(*bgsprite).second.setTextureRect(sf::IntRect(viewRect.left/3, viewRect.top/3, viewRect.width, viewRect.height));

	for(multimap<float, map<string, sf::Sprite>::iterator>::iterator i = backgroundObjects.begin(); i != backgroundObjects.end(); i++)
	{
		(*(*i).second).second.setPosition(viewRect.left, viewRect.top);
		(*(*i).second).second.setTextureRect(sf::IntRect(viewRect.left / (*i).first, viewRect.top / (*i).first, viewRect.width, viewRect.height));
	}

}

Background::~Background()
{
}
