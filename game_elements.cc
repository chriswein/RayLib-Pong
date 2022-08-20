#include "./include/raylib.h"
#include "engine.h"
#include <memory>
#include <iostream>
#pragma once
class paddle : public drawable, public boxcollision, public keylistener
{
public:
	int id_;
	Rectangle coords;
	bool moving = false;
	int direction = 0;
	paddle(int id, Rectangle vec)
	{
		this->id_ = id;
		this->coords = vec;
	}
	~paddle()
	{
		std::cout << "deconstructed paddle: " << this->id_ << std::endl;
	}
	virtual void draw()
	{
		DrawRectangle(this->coords.x, this->coords.y, this->coords.width, this->coords.height, BLACK);
	}
	virtual void update()
	{
	}
	virtual bool check(std::shared_ptr<boxcollision> partner)
	{
		return CheckCollisionRecs(partner->get(), this->get());
	}
	Rectangle get()
	{
		return this->coords;
	}
	virtual void collision(std::shared_ptr<boxcollision> partner)
	{
	}
	virtual int id()
	{
		return this->id_;
	}
	virtual void keyEvent(int event, int key)
	{
		if (event == KEY_DOWN)
		{
			this->moving = true;
			this->direction = key;
			this->coords.y += (key == 0) ? -10 : 10;
		}
		else
		{
			this->moving = false;
		}
	}
	virtual MovementInfo moveStatus()
	{
		return {this->moving, this->direction};
	}
};

class Wall : public paddle
{
public:
	Wall(Rectangle r) : paddle(123, r)
	{
	}
	Wall(int id, Rectangle r) : paddle(id, r)
	{
	}
	virtual void draw() {}
};

class ball : public drawable, public boxcollision
{
private:
	bool checkInBounds()
	{
		if (this->pos.x + this->pos.width * 2 < 0)
			return false;
		if (this->pos.x > WIDTH)
			return false;
		if (this->pos.y + this->pos.height * 2 < 0)
			return false;
		if (this->pos.y > HEIGHT)
			return false;

		return true;
	}

public:
	Rectangle pos;
	Vector2 impulse;
	int lastCollisionPaddle = 0;
	bool living = true;
	ball(Rectangle pos, Vector2 impulse)
	{
		this->pos = pos;
		this->impulse = impulse;
	}
	virtual void draw()
	{
		// update();
		Vector2 middle = this->middle();
		DrawCircle(middle.x, middle.y, this->pos.width * 2.0f, BLACK);
	}
	~ball()
	{
		std::cout << "decontructed ball" << std::endl;
	}
	Vector2 middle()
	{
		Vector2 v;
		v.x = this->pos.x + this->pos.width;
		v.y = this->pos.y + this->pos.height;
		return v;
	}
	virtual void update()
	{
		this->pos.x += this->impulse.x;
		this->pos.y += this->impulse.y;
		if (!this->checkInBounds())
			this->living = false;
	}

	virtual bool check(std::shared_ptr<boxcollision> partner)
	{
		auto rect = partner->get();
		Vector2 v = this->middle();
		return CheckCollisionCircleRec(v, 1.0f + this->pos.width, rect);
	}
	virtual Rectangle get()
	{
		Rectangle r{this->pos.x, this->pos.y, this->pos.width * 2, this->pos.height * 2};
		return r;
	}
	virtual void collision(std::shared_ptr<boxcollision> partner)
	{

		// This was a paddle
		if (0 < partner->id() && partner->id() < 3)
			this->lastCollisionPaddle = partner->id();

		MovementInfo m = partner->moveStatus();

		switch (partner->id())
		{
		case PADDLE1:
			this->impulse.x *= -1;
			if (m.moving)
			{
				this->impulse.y = (m.direction == 0) ? -1 * abs(this->impulse.y) : abs(this->impulse.y);
			}
			break;
		case PADDLE2:
			this->impulse.x *= -1;
			if (m.moving)
			{
				this->impulse.y = (m.direction == 0) ? -1 * abs(this->impulse.y) : abs(this->impulse.y);
			}
			break;
		case TOPWALL:
			this->impulse.y *= -1;
			break;
		case BOTTOMWALL:
			this->impulse.y *= -1;
			break;
		default:
			break;
		}

		this->update();
	}
	virtual int id()
	{
		return 9999;
	}
	virtual MovementInfo moveStatus()
	{
		return {true, -1};
	}
};
