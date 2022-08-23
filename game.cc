#include "game.h"

void Game::drawPoints()
{
	string label = std::to_string(this->state->getValue("P1")) + ":" + std::to_string(this->state->getValue("P2"));
	DrawText(label.c_str(), (WIDTH / 2) - 50, 25, 36, DARKBROWN);
}

Game::Game(std::function<void(Level *)> callback, shared_ptr<AudioManager> am, shared_ptr<StateManager> state) : Level(callback)
{
	this->id = GAME;
	this->p = make_unique<Pause>(Pause(callback));
	this->am = am;
	this->state = state;
}
void Game::init()
{
	this->game_elements =
		make_shared<vector<shared_ptr<drawable>>>(vector<shared_ptr<drawable>>());

	this->collision_elements =
		make_shared<vector<shared_ptr<boxcollision>>>(vector<shared_ptr<boxcollision>>());

	this->paddle1 = std::make_shared<paddle>(paddle(PADDLE1, {0, 260, 20, 200}));
	this->paddle2 = std::make_shared<paddle>(paddle(PADDLE2, {WIDTH - 20, 260, 20, 200}));
	this->top = std::make_shared<Wall>(Wall(TOPWALL, {0, -10, WIDTH, 10}));
	this->bottom = std::make_shared<Wall>(Wall(BOTTOMWALL, {0, HEIGHT, WIDTH, 10}));
	this->ball1 = std::make_shared<ball>(ball({WIDTH / 2, 360, 10, 10}, {18, 1}, this->am, this->state));
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

void Game::update()
{
	if (!this->paused)
	{
		drawPoints();
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
		if (IsKeyPressed(KEY_ESCAPE))
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
			this->init();
		}
	}
	else
	{
		this->p->update();
		if (IsKeyPressed(KEY_ESCAPE))
		{
			this->paused = !this->paused;
		}
	}
}
void Game::draw()
{
	if (!this->paused)
	{
		for (auto i : *(this->game_elements))
		{
			i->draw();
		}
	}
	else
	{
		this->p->draw();
	}
}

Title::Title(std::function<void(Level *)> callback, std::shared_ptr<AudioManager> am, shared_ptr<StateManager> state) : Level(callback)
{
	this->id = TITLE;
	this->am = am;
	this->state = state;
}

void Title::update()
{
	if (GetTime() > start + 5)
	{
		this->am->play("wgcoin.wav");
		Game *g = new Game(this->callback, this->am, this->state);
		this->callback(g);
		//((void(*)(void*))this->callback)(nullptr);//&g);
	}
}
void Title::draw()
{
	DrawText("Weingame", (WIDTH / 2) - 50, (HEIGHT / 2) - 25, 24, BLACK);
}
void Title::init()
{
	this->start = GetTime();
}
