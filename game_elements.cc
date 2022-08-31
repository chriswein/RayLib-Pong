#include "game_elements.h"

paddle::paddle(int id, Rectangle vec)
{
	this->id_ = id;
	this->coords = vec;
}
paddle::~paddle()
{
}
void paddle::draw()
{
	DrawRectangle(this->coords.x, this->coords.y, this->coords.width, this->coords.height, BLACK);
}
void paddle::update()
{
}
bool paddle::check(std::shared_ptr<boxcollision> partner)
{
	return CheckCollisionRecs(partner->get(), this->get());
}
Rectangle paddle::get()
{
	return this->coords;
}
void paddle::collision(std::shared_ptr<boxcollision> partner)
{
}
int paddle::id()
{
	return this->id_;
}
void paddle::keyEvent(int event, int key)
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
MovementInfo paddle::moveStatus()
{
	return {this->moving, this->direction};
}

Wall::Wall(Rectangle r) : paddle(123, r)
{
}
Wall::Wall(int id, Rectangle r) : paddle(id, r)
{
}
void Wall::draw() {}

bool ball::checkInBounds()
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

ball::ball(Rectangle pos, Vector2 impulse, shared_ptr<AudioManager> am, shared_ptr<StateManager> state)
{
	this->pos = pos;
	this->impulse = impulse;
	this->am = am;
	this->state = state;
}
void ball::draw()
{
	// update();
	Vector2 middle = this->middle();
	DrawCircle(middle.x, middle.y, this->pos.width * 2.0f, BLACK);
}
ball::~ball()
{
	
}
Vector2 ball::middle()
{
	Vector2 v;
	v.x = this->pos.x + this->pos.width;
	v.y = this->pos.y + this->pos.height;
	return v;
}
void ball::update()
{
	this->pos.x += this->impulse.x;
	this->pos.y += this->impulse.y;
	if (!this->checkInBounds())
	{
		this->living = false;
		this->am->play("./assets/out.wav");
		this->state->increaseValue("P" + std::to_string(this->lastCollisionPaddle));
	}
}

bool ball::check(std::shared_ptr<boxcollision> partner)
{
	auto rect = partner->get();
	Vector2 v = this->middle();
	return CheckCollisionCircleRec(v, 1.0f + this->pos.width, rect);
}
Rectangle ball::get()
{
	Rectangle r{this->pos.x, this->pos.y, this->pos.width * 2, this->pos.height * 2};
	return r;
}
void ball::collision(std::shared_ptr<boxcollision> partner)
{

	// Partner was a paddle
	if (0 < partner->id() && partner->id() < 3)
		this->lastCollisionPaddle = partner->id();

	MovementInfo m = partner->moveStatus();
	float rand_ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	rand_ += 1;
	switch (partner->id())
	{
	case PADDLE1:
		this->impulse.x *= -1.02;
		// PlaySound(this->am);
		this->am->play("./assets/hit.wav");
		if (m.moving)
		{
			this->impulse.y = (m.direction == 0) ? -1 * abs(this->impulse.y * rand_) : abs(this->impulse.y * rand_);
		}
		break;
	case PADDLE2:
		this->impulse.x *= -1.02;
		// PlaySound(this->fxWav);
		this->am->play("./assets/hit.wav");
		if (m.moving)
		{
			this->impulse.y = (m.direction == 0) ? -1 * abs(this->impulse.y * rand_) : abs(this->impulse.y * rand_);
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
int ball::id()
{
	return 9999;
}
MovementInfo ball::moveStatus()
{
	return {true, -1};
}
