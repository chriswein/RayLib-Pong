#include "raylib.h"
#include "engine.h"
#include "game_elements.cc"
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

class Level
{
	/**
	 *  Loads all game elements
	 **/
public:
	function<void(Level *)> callback;
	// void* callback;
	int id = LEVEL;
	Level(std::function<void(Level *)> callback)
	{
		this->callback = callback;
	}
	virtual void init() { cout << "Level Init called" << endl; };
	virtual void update(){};
	virtual void draw(){};
};

class Pause : public Level
{
public:
	double start;
	Pause(std::function<void(Level *)> callback) : Level(callback)
	{
		this->id = TITLE;
	}
	void update()
	{
	}
	void draw()
	{
		DrawText("Pause", WIDTH / 2, HEIGHT / 2, 24, BLACK);
	}
	void init()
	{
		this->start = GetTime();
	}
};

