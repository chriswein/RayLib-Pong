#include "raylib.h"
#include "engine.h"
#include <memory>
#include <vector>
#include <functional>
using namespace std;
#pragma once

enum LEVELID
{
	LEVEL,
	GAME,
	TITLE
};

/**
 * @brief Loads all game elements
 * 
 */
class Level
{
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


