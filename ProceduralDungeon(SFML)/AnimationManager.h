#pragma once
#include "Animation.h"

class AnimationManager 
{
private:
	map<string, Animation> animations;
	string currentAnimation;
	int angle;
public:
	AnimationManager();
	void addAnimation(string name, Animation anim);
	void addAnimation(string name);
	void addFrame(string animation, ResourceManager & rm, string path, sf::IntRect rect);
	void setCurrentAnimation(string name);
	void tick();
	void setAngle(int angle);
	map<string, sf::Sprite>::iterator & getCurrentFrame();
	~AnimationManager();
};

