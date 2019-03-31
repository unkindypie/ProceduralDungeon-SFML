#include "AnimationManager.h"



AnimationManager::AnimationManager()
{
	angle = 0;
}

void AnimationManager::addAnimation(string name, Animation anim)
{
	animations.emplace(name, anim);
}

void AnimationManager::addAnimation(string name)
{
	animations.emplace(name, Animation());
}

void AnimationManager::addFrame(string animation, ResourceManager & rm, string path, sf::IntRect rect)
{
	animations[animation].addFrame(rm, path, rect);
}

void AnimationManager::setCurrentAnimation(string name)
{
	currentAnimation = name;
}

map<string, sf::Sprite>::iterator & AnimationManager::getCurrentFrame()
{
	animations[currentAnimation].setAngle(angle);
	return animations[currentAnimation].getCurrrentFrame();
}

void AnimationManager::tick()
{
	animations[currentAnimation].tick();
}

void AnimationManager::setAngle(int angle)
{
	this->angle = angle;
	animations[currentAnimation].setAngle(angle);
}

AnimationManager::~AnimationManager()
{
}
