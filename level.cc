#include "level.h"

Level::Level(std::function<void(Level *)> callback)
{
	this->callback = callback;
}

Pause::Pause(std::function<void(Level *)> callback) : Level(callback)
{
	this->id = TITLE;
}
void Pause::update()
{
}
void Pause::draw()
{
	DrawText("Pause", (WIDTH / 2) - 40, (HEIGHT / 2) - 30, 24, BLACK);
}
void Pause::init()
{
	this->start = GetTime();
}
