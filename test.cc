#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "./include/raylib.h"

#include "engine.h"
#include "game_elements.cc"
#include "level.cc"
#include "game.cc"
#include "audio.cc"

#define prnt(x) std::cout << x << std::endl;

bool GAME_RUNNING = true;

Level *current_level;
shared_ptr<AudioManager> am(nullptr);

/**
 * @brief Gets called by level if another level needs to be called;
 *
 * @param level
 */
void changeLevelRequest(Level *level)
{
    std::cout << "Change of Level requested" << std::endl;
    // Clean up previous level
    free((void *)current_level);
    // Hook up the new one and init
    current_level = level;
    current_level->init();
}
std::function<void(Level *)> cb = &changeLevelRequest;

void init()
{

// current_level = make_shared<Game>(Game(cb));
#ifndef NOTITLE
    current_level = new Title(cb, am); // new Game(cb);
#endif
#ifdef NOTITLE
    current_level = new Game(cb, am);
#endif
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
    InitAudioDevice();
    am = make_shared<AudioManager>(AudioManager());
    am->add("hit.wav");
    am->add("out.wav");
    am->add("wgcoin.wav");
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
    am = nullptr;
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
