#pragma once
#include <iostream>
#include <fstream>
#include <string>

class ConfigurationReader
{
	float windowWidth;
	float windowHeight;
	float enemyMultiplier;
public:
	ConfigurationReader();
	~ConfigurationReader();
};

