#include "raylib.h"
#include "engine.h"
#include <memory>
#include <vector>
#include <functional>
#include "game_elements.h"
using namespace std;
#pragma once

enum LEVELID
{
	LEVEL,
	GAME,
	TITLE
};

class Level
{
	/**
	 *  Loads all game elements
	 **/
public:
	function<void(Level *)> callback;
	// void* callback;
	int id = LEVEL;
	Level(std::function<void(Level *)> callback);
	virtual void init() {};
	virtual void update(){};
	virtual void draw(){};
};

class Pause : public Level
{
public:
	double start;
	Pause(std::function<void(Level *)> callback);
	void update();
	void draw();
	void init();
};


