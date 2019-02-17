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
void Block::setBlockType(BlockType type, ResourceManager & rm, direction dir)
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
		//left_, right_, top, down
		if (dir == top) sprite_iterator = rm.loadSprite("images/topwall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == left_) sprite_iterator = rm.loadSprite("images/left_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == right_) sprite_iterator = rm.loadSprite("images/right_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == down) sprite_iterator = rm.loadSprite("images/bottomwall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == left_top_angle) sprite_iterator = rm.loadSprite("images/left_top_angle_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == left_bottom_angle) sprite_iterator = rm.loadSprite("images/left_bottom_angle_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == right_top_angle) sprite_iterator = rm.loadSprite("images/right_top_angle_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == right_bottom_angle) sprite_iterator = rm.loadSprite("images/right_bottom_angle_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		updateRect();
		break;
	default:
		break;
	}
}
Block::Block(size_t x, size_t y, BlockType type, ResourceManager & rm, direction dir)
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
		//left_, right_, top, down
		if(dir == top) sprite_iterator = rm.loadSprite("images/topwall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if(dir == left_) sprite_iterator = rm.loadSprite("images/left_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == right_) sprite_iterator = rm.loadSprite("images/right_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if(dir == down) sprite_iterator = rm.loadSprite("images/bottomwall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if(dir == left_top_angle) sprite_iterator = rm.loadSprite("images/left_top_angle_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if(dir == left_bottom_angle) sprite_iterator = rm.loadSprite("images/left_bottom_angle_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == right_top_angle) sprite_iterator = rm.loadSprite("images/right_top_angle_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		if (dir == right_bottom_angle) sprite_iterator = rm.loadSprite("images/right_bottom_angle_wall.png", sf::IntRect(0, 0, COMMON_SPRITE_SIZE, COMMON_SPRITE_SIZE));
		updateRect();
		break;
	default:
		break;
	}
}

Block::~Block()
{
}
