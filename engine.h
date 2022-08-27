#pragma once
#include "./include/raylib.h"
#include <memory>
#include <string>
#include <map>

#define WIDTH 1280
#define HEIGHT 720
#define PADDLE1 1
#define PADDLE2 2
#define TOPWALL 3
#define BOTTOMWALL 4
#define INTRAFRAMETIME 0.012

/**
 * @brief Main class enabling the game loop to draw and update an element
 *
 */
class drawable
{
public:
#ifdef PLATFORM_WEB
	virtual void draw(){};
	virtual void update(){};

#else
	virtual void draw();
	virtual void update();

#endif
};

typedef struct
{
	bool moving;
	int direction;
	float speed;
} MovementInfo;

/**
 * @brief Game elements need to implement this if they need collision detection
 *
 */
class boxcollision
{
public:
#ifdef PLATFORM_WEB

	virtual Rectangle get(){};
	virtual bool check(std::shared_ptr<boxcollision> partner){};
	virtual void collision(std::shared_ptr<boxcollision> partner){};
	virtual int id(){};
	virtual MovementInfo moveStatus(){};
#else
	virtual Rectangle get();
	virtual bool check(std::shared_ptr<boxcollision> partner);
	virtual void collision(std::shared_ptr<boxcollision> partner);
	virtual int id();
	virtual MovementInfo moveStatus();

#endif
};

class keylistener
{
#ifdef PLATFORM_WEB
	virtual void keyEvent(int event, int key){};
#else
	virtual void keyEvent(int event, int key);
#endif
};

/**
 * @brief Used to keep track of the game score and other variables
 *
 */
class StateManager
{
	std::map<std::string, int> memory;

public:
	void increaseValue(std::string value);
	int getValue(std::string key);
	void setValue(std::string key, int value);
};