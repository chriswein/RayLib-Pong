#include "level.h"

class Game : public Level
{
	shared_ptr<vector<shared_ptr<drawable>>> game_elements;
	shared_ptr<vector<shared_ptr<boxcollision>>> collision_elements;
	std::shared_ptr<paddle> paddle1;
	std::shared_ptr<paddle> paddle2;
	std::shared_ptr<Wall> top;
	std::shared_ptr<Wall> bottom;
	std::shared_ptr<ball> ball1;
	bool paused = false;
	std::unique_ptr<Pause> p;
	shared_ptr<AudioManager> am;
	shared_ptr<StateManager> state;

	void drawPoints();

public:
	Game(std::function<void(Level *)> callback, shared_ptr<AudioManager> am, shared_ptr<StateManager> state);
	void init();
	void update();
	void draw();
};

class Title : public Level
{
public:
	double start;
	std::shared_ptr<AudioManager> am;
	shared_ptr<StateManager> state;
	Title(std::function<void(Level *)> callback, std::shared_ptr<AudioManager> am, shared_ptr<StateManager> state); 
	void update();
	void draw();
	void init();
};
