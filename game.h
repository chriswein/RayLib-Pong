#pragma once
#include "raylib.h"
#include <memory>

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
};