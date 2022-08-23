#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "./include/raylib.h"

#include "engine.h"
#include "game_elements.h"
#include "level.h"
#include "game.h"
#include "audio.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

#define prnt(x) std::cout << x << std::endl;

bool GAME_RUNNING = true;
double next_frame;

Level *current_level;
shared_ptr<AudioManager> am(nullptr);
shared_ptr<StateManager> state(nullptr);

/**
 * @brief Gets called by level if another level needs to be called;
 *
 * @param level
 */
void changeLevelRequest(Level *level)
{
    // Clean up previous level
    free((void *)current_level);
    // Hook up the new one and init
    current_level = level;
    current_level->init();
}
std::function<void(Level *)> cb = &changeLevelRequest;

void init()
{

#ifndef NOTITLE
    current_level = new Title(cb, am, state); // new Game(cb);
#endif
#ifdef NOTITLE
    current_level = new Game(cb, am, state);
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

void emsloop(void)
{

    if (GetTime() > next_frame)
    {
        update();
        next_frame = GetTime() + INTRAFRAMETIME;
    }
    render();
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Pong");
    next_frame = GetTime() + INTRAFRAMETIME;
    InitAudioDevice();

    am = make_shared<AudioManager>(AudioManager());
    am->add("./assets/hit.wav");
    am->add("./assets/out.wav");
    am->add("./assets/wgcoin.wav");

    state = make_shared<StateManager>(StateManager());
    state->setValue("P1", 0);
    state->setValue("P2", 0);

    SetExitKey(KEY_BACKSPACE);
    init();
    HideCursor();
#ifdef PLATFORM_WEB // Emscripten does not work well with busy waiting
    emscripten_set_main_loop(emsloop, 0, 1);
#else
    SetTargetFPS(60);
    while ((GAME_RUNNING = !WindowShouldClose()))
    {
        if (GetTime() > next_frame)
        {
            update();
            next_frame = GetTime() + INTRAFRAMETIME;
        }
        render();
    }
#endif
    am = nullptr;
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
