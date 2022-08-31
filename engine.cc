#include "engine.h"
#include <iostream>

int StateManager::getValue(std::string key)
{
	if (this->memory.count(key) > 0)
	{
		return this->memory[key];
	}
	return 0;
}

void StateManager::setValue(std::string key, int value)
{
	this->memory[key] = value;
}

void StateManager::increaseValue(std::string key)
{
	this->memory[key] += 1;
}