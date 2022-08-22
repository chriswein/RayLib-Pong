#include "./include/raylib.h"
#include <memory>
#include <iostream>
#include <limits.h>
#include "engine.h"
#include "audio.h"
#pragma once

class paddle : public drawable, public boxcollision, public keylistener
{
public:
	int id_;
	Rectangle coords;
	bool moving= false;
	int direction = 0;
	paddle(int id, Rectangle vec);
	~paddle();
	virtual void draw();
	virtual void update();
	virtual bool check(std::shared_ptr<boxcollision> partner);
	Rectangle get();
	virtual void collision(std::shared_ptr<boxcollision> partner);
	virtual int id();
	virtual void keyEvent(int event, int key);
	virtual MovementInfo moveStatus();
};

class Wall : public paddle
{
public:
	Wall(Rectangle r);
	Wall(int id, Rectangle r);
	virtual void draw(); 
};

class ball : public drawable, public boxcollision
{
private:
	bool checkInBounds();

public:
	Rectangle pos;
	Vector2 impulse;
	int lastCollisionPaddle = 0;
	bool living = true;
	shared_ptr<StateManager> state;
	// Sound fxWav;
	shared_ptr<AudioManager> am;
	ball(Rectangle pos, Vector2 impulse, shared_ptr<AudioManager> am, shared_ptr<StateManager> state);
	virtual void draw();
	~ball();
	Vector2 middle();
	virtual void update();

	virtual bool check(std::shared_ptr<boxcollision> partner);
	virtual Rectangle get();
	virtual void collision(std::shared_ptr<boxcollision> partner);
	virtual int id();
	virtual MovementInfo moveStatus();
};
