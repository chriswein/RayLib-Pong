#include "raylib.h"
#include "game.h"
#include <memory>
#include <iostream>

class paddle : public drawable, public boxcollision
{
public:
	int id;
	Rectangle coords;
	paddle(int id, Rectangle vec)
	{
		this->id = id;
		this->coords = vec;
	}
	~paddle(){
			std::cout << "deconstructed paddle: " << this->id << std::endl;
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
	virtual void collision(std::shared_ptr<boxcollision> partner){
	 	//std::cout << "rect collision" << std::endl;
	}
};

class ball : public drawable, public boxcollision
{
public:
	Rectangle pos;
	Vector2 impulse;
	ball(Rectangle pos, Vector2 impulse)
	{
		this->pos = pos;
		this->impulse = impulse;
	}
	virtual void draw()
	{
		update();
		DrawCircle(this->pos.x + this->pos.width, this->pos.y + this->pos.height, 20.0f, BLACK);
	}
	~ball(){
			std::cout << "decontructed ball" << std::endl;
	}
	virtual void update()
	{
		this->pos.x += this->impulse.x;
		this->pos.y += this->impulse.y;
	}
	virtual bool check(std::shared_ptr<boxcollision> partner)
	{
		auto rect = partner->get();
		Vector2 v = {this->pos.x + this->pos.width, this->pos.y + this->pos.height};
		return CheckCollisionCircleRec(v, 20.0f, rect);
	}
	virtual Rectangle get()
	{
		Rectangle r{this->pos.x - this->pos.width, this->pos.y - this->pos.height, this->pos.width*2, this->pos.height*2};
		return this->pos;
	}
	virtual void collision(std::shared_ptr<boxcollision> partner){
	 	std::cout << "ball collision" << std::endl;
		this->impulse.x *= -1;	
		this->update();
	}
};
