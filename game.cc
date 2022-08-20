#include "level.cc"

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

public:
	Game(std::function<void(Level *)> callback) : Level(callback)
	{
		this->id = GAME;
		this->p = make_unique<Pause>(Pause(callback));
	}
	void init()
	{
		this->game_elements =
			make_shared<vector<shared_ptr<drawable>>>(vector<shared_ptr<drawable>>());

		this->collision_elements =
			make_shared<vector<shared_ptr<boxcollision>>>(vector<shared_ptr<boxcollision>>());

		this->paddle1 = std::make_shared<paddle>(paddle(PADDLE1, {0, 200, 20, 200}));
		this->paddle2 = std::make_shared<paddle>(paddle(PADDLE2, {WIDTH - 20, 0, 20, 200}));
		this->top = std::make_shared<Wall>(Wall(TOPWALL, {0, -10, WIDTH, 10}));
		this->bottom = std::make_shared<Wall>(Wall(BOTTOMWALL, {0, HEIGHT, WIDTH, 10}));
		this->ball1 = std::make_shared<ball>(ball({WIDTH / 2, 100, 10, 10}, {18, -1}));
		std::cout << "init game elements done" << std::endl;
		game_elements->push_back(std::dynamic_pointer_cast<drawable>(paddle1));
		game_elements->push_back(std::dynamic_pointer_cast<drawable>(paddle2));
		game_elements->push_back(std::dynamic_pointer_cast<drawable>(top));
		game_elements->push_back(std::dynamic_pointer_cast<drawable>(bottom));
		game_elements->push_back(std::dynamic_pointer_cast<drawable>(ball1));

		collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(paddle1));
		collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(paddle2));
		collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(top));
		collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(bottom));
		collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(ball1));
	}
	void update()
	{
		if (!this->paused)
		{
			for (auto i : *(this->game_elements))
			{
				i->update();
			}
if (IsKeyDown(KEY_UP))
			{
				this->paddle2->keyEvent(KEY_DOWN, 0);
			}
			if (IsKeyDown(KEY_DOWN))
			{

				this->paddle2->keyEvent(KEY_DOWN, 1);
			}
			if (IsKeyDown(KEY_S))
			{
				this->paddle1->keyEvent(KEY_DOWN, 1);
			}
			if (IsKeyDown(KEY_W))
			{
				this->paddle1->keyEvent(KEY_DOWN, 0);
			}
			// KEYUP
			if (IsKeyReleased(KEY_UP))
			{
				this->paddle2->keyEvent(KEY_UP, 0);
			}
			if (IsKeyReleased(KEY_DOWN))
			{
				this->paddle2->keyEvent(KEY_UP, 1);
			}
			if (IsKeyReleased(KEY_S))
			{
				this->paddle1->keyEvent(KEY_UP, 0);
			}
			if (IsKeyReleased(KEY_W))
			{
				this->paddle1->keyEvent(KEY_UP, 1);
			}
			if (IsKeyDown(KEY_F))
			{
				ToggleFullscreen();
			}
			if (IsKeyPressed(KEY_PAUSE))
			{
				this->paused = !this->paused;
			}
			auto i = this->collision_elements->begin();
			while (i < this->collision_elements->end())
			{
				auto j = i + 1;
				while (j < this->collision_elements->end())
				{
					if ((*i)->check((*j)))
					{
						(*j)->collision((*i));
					}
					j++;
				}
				i++;
			}
			// Is the ball still in the game?
			if (!this->ball1->living)
			{
				std::cout << "Game over" << std::endl;
				std::cout << "Winner was:" << std::endl;
				std::cout << this->ball1->lastCollisionPaddle << std::endl;

				this->init();
			}
		}
		else
		{
			this->p->update();
			if (IsKeyPressed(KEY_PAUSE))
			{
				this->paused = !this->paused;
			}
		}
	}
	void draw()
	{
		if (!this->paused)
		{
			for (auto i : *(this->game_elements))
			{
				i->draw();
			}
		}else{
			this->p->draw();
		}
	}
};

class Title : public Level
{
public:
	double start;
	Title(std::function<void(Level *)> callback) : Level(callback)
	{
		this->id = TITLE;
	}
	void update()
	{
		if (GetTime() > start + 5)
		{
			Game *g = new Game(this->callback);
			this->callback(g);
			//((void(*)(void*))this->callback)(nullptr);//&g);
		}
	}
	void draw()
	{
		DrawText("Weingame", WIDTH / 2, HEIGHT / 2, 24, BLACK);
	}
	void init()
	{
		this->start = GetTime();
	}
};
