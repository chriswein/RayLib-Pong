#include <vector>
#include <memory>
#include <iostream>

#include "./include/raylib.h"

#include "game.h"
#include "game_elements.cc"

#define prnt(x) std::cout << x << std::endl;

std::shared_ptr<paddle> paddle1(nullptr);
std::shared_ptr<paddle> paddle2(nullptr);
std::shared_ptr<Wall> top(nullptr);
std::shared_ptr<Wall> bottom(nullptr);
std::shared_ptr<ball> ball1(nullptr);
bool GAME_RUNNING = true;
std::vector<std::shared_ptr<drawable>> *game_elements;
std::vector<std::shared_ptr<boxcollision>> *collision_elements;

void init()
{
    prnt("initialized");

    paddle1 = std::make_shared<paddle>(paddle(PADDLE1, {0, 200, 20, 200}));
    paddle2 = std::make_shared<paddle>(paddle(PADDLE2, {WIDTH - 20, 0, 20, 200}));
    top = std::make_shared<Wall>(Wall(TOPWALL,{0, -10, WIDTH, 10}));
    bottom = std::make_shared<Wall>(Wall(BOTTOMWALL,{0, HEIGHT , WIDTH, 10}));
    ball1 = std::make_shared<ball>(ball({WIDTH / 2, 100, 10, 10}, {12, -1}));

    game_elements = new std::vector<std::shared_ptr<drawable>>();
    game_elements->push_back(std::dynamic_pointer_cast<drawable>(paddle1));
    game_elements->push_back(std::dynamic_pointer_cast<drawable>(paddle2));
    game_elements->push_back(std::dynamic_pointer_cast<drawable>(top));
    game_elements->push_back(std::dynamic_pointer_cast<drawable>(bottom));
    game_elements->push_back(std::dynamic_pointer_cast<drawable>(ball1));

    collision_elements = new std::vector<std::shared_ptr<boxcollision>>();
    collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(paddle1));
    collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(paddle2));
    collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(top));
    collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(bottom));
    collision_elements->push_back(std::dynamic_pointer_cast<boxcollision>(ball1));
}

void render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (auto i : *game_elements)
    {
        i->draw();
    }

    EndDrawing();
}

void update()
{
    if (IsKeyDown(KEY_UP))
    {
        paddle2->coords.y -= 10;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        paddle2->coords.y += 10;
    }
    if (IsKeyDown(KEY_S))
    {
        paddle1->coords.y += 10;
    }
    if (IsKeyDown(KEY_W))
    {
        paddle1->coords.y -= 10;
    }
    if (IsKeyDown(KEY_F))
    {
        ToggleFullscreen();
        SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    }

    auto i = collision_elements->begin();
    while (i < collision_elements->end())
    {
        auto j = i + 1;
        while (j < collision_elements->end())
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
    if (!ball1->living)
    {
        prnt("Game over");
        prnt("Winner was:");
        prnt(ball1->lastCollisionPaddle);

        init();
    }
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Pong");
    SetTargetFPS(60);
    init();

    while ((GAME_RUNNING = !WindowShouldClose()))
    {
        update();
        render();
    }

    CloseWindow();

    return 0;
}
