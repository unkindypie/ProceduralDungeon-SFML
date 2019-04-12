#pragma once
#include "Content.h"

enum BlockType
{
	none, brick
};
class Block : public Content
{
public:
	BlockType type;
	Block();
	Block(size_t x, size_t y, BlockType type, ResourceManager & rm, direction dir);
	void setBlockType(BlockType type, ResourceManager & rm, direction dir);
	void draw(sf::RenderTarget & win);
	void update();
	~Block();
};

