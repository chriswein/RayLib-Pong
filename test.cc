#include <vector>
#include <memory>
#include <iostream>

#include "./include/raylib.h"

#include "game.h"
#include "game_elements.cc"
#include "level.cc"

#define prnt(x) std::cout << x << std::endl;

bool GAME_RUNNING = true;

void changeLevelRequest(void * level){
    std::cout << "Change of Level requested" << std:: endl;
    if (level == nullptr) {
        std::cout << "no new level provided" << std:: endl;
        CloseWindow();
        return;
    }
    Level* l = (Level*) level;
}

unique_ptr<Level> current_level(new Game(&changeLevelRequest));

void init()
{
    prnt("initialized");
    current_level->init();
}

void render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
        current_level->draw();
    EndDrawing();
}

void update()
{
    current_level->update();
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Pong");
    double next = GetTime() + INTRAFRAMETIME;
    SetTargetFPS(60);
    init();
    HideCursor();

    while ((GAME_RUNNING = !WindowShouldClose()))
    {
        if (GetTime() > next)
        {
            update();
            next = GetTime() + INTRAFRAMETIME;
        }
        render();
    }

    CloseWindow();

    return 0;
}
