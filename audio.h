#include "./include/raylib.h"
#include <string>
#include <map>
#include <iostream>
#pragma once
using namespace std;

class AudioManager
{
	map<string, Sound> sounds;

public:
	AudioManager();
	~AudioManager();
	void add(const char *name);
	void play(string name);
};