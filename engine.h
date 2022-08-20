#pragma once
#include "./include/raylib.h"
#include <memory>

#define WIDTH 1280
#define HEIGHT 720
#define PADDLE1 1
#define PADDLE2 2
#define TOPWALL 3
#define BOTTOMWALL 4
#define INTRAFRAMETIME 0.012

class drawable
{
public:
    virtual void draw();
    virtual void update();
};

typedef struct {
	bool moving;
	int direction;
	float speed;
}MovementInfo;

class boxcollision{
	public: 
	virtual Rectangle get();
	virtual bool check(std::shared_ptr<boxcollision> partner);
	virtual void collision(std::shared_ptr<boxcollision> partner);
	virtual int id();
	virtual MovementInfo moveStatus();
};

class keylistener{
	virtual void keyEvent(int event, int key);
};