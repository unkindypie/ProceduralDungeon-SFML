#include "Block.h"
//#include <windows.h>


Block::Block()
{
	type = none;

}
void Block::draw(sf::RenderWindow & win)
{
	//drawBlock(*this);
	if(type != none)
	{
		sprite_iterator->second.setPosition(x, y);
	/*	sf::Texture texture;
		texture.loadFromFile("images/blocks.png");
		sf::Sprite tmp(texture);
		tmp.setTextureRect(sf::IntRect(0, 0, 64, 64));
		tmp.setPosition(x * 64, y * 64);*/
		win.draw(sprite_iterator->second);
		sprite_iterator->second.setPosition(0, 0);
	}
}
void Block::update(float elapsedTime)
{
	if(!isRendered)
	{
		//draw();
		//isRendered = 1;
	}
}
void Block::setBlockType(BlockType type, ResourceManager & rm)
{
	this->type = type;
	switch (type)
	{
	case none:
		collides = false;
		rect = sf::FloatRect(x, y, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE);
		break;
	case brick:
		collides = true;
		sprite_iterator = rm.loadSprite("images/blocks16x16.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		updateRect();
		break;
	default:
		break;
	}
}
Block::Block(size_t x, size_t y, BlockType type, ResourceManager & rm)
{
	this->x = x;
	this->y = y;
	this->type = type;
	hitable = false;
	
	switch (type)
	{
	case none:
		collides = false;
		rect = sf::FloatRect(x, y, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE);
		break;
	case brick:
		collides = true;
		sprite_iterator = rm.loadSprite("images/blocks16x16.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		updateRect();
		break;
	default:
		break;
	}
}

Block::~Block()
{
}
