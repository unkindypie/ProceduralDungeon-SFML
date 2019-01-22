#include "Block.h"


Block::Block()
{
	type = none;

}
void Block::draw(sf::RenderWindow & win)
{
	if(type != none)
	{
		sprite_iterator->second.setPosition(x, y);
		win.draw(sprite_iterator->second);
		sprite_iterator->second.setPosition(0, 0);
	}
}
void Block::update(float elapsedTime)
{

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
