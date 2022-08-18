#pragma once
#include "./include/raylib.h"
#include <memory>

#define WIDTH 1280
#define HEIGHT 720
#define PADDLE1 1
#define PADDLE2 2
#define TOPWALL 3
#define BOTTOMWALL 4

class drawable
{
public:
    virtual void draw();
    virtual void update();
};

class boxcollision{
	public: 
	virtual Rectangle get();
	virtual bool check(std::shared_ptr<boxcollision> partner);
	virtual void collision(std::shared_ptr<boxcollision> partner);
	virtual int id();
};