#include <vector>
#include <memory>
#include <iostream>

#include "raylib.h"

#include "game.h"
#include "game_elements.cc"

std::shared_ptr<paddle> paddle1(new paddle(0, {0, 0, 20, 400}));
std::shared_ptr<paddle> paddle2(new paddle(1, {1280 - 20, 0, 20, 400}));
std::shared_ptr<ball> ball1(new ball({1280/2, 720/2, 10,10}, {3,0}));
bool GAME_RUNNING = true;
std::vector<std::shared_ptr<drawable>> game_elements;
std::vector<std::shared_ptr<boxcollision>> collision_elements;

void render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (auto i : game_elements)
    {
        i->draw();
    }

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
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
    if(IsKeyDown(KEY_F)){
        ToggleFullscreen();
    }

    auto i = collision_elements.begin();
    while (i < collision_elements.end())
    {
        auto j = i+1;
        while(j < collision_elements.end()){
            if((*i)->check( (*j) )){
                (*j)->collision((*i));
            }
            j++;
        }
        i++;
    }
    
}

void init()
{
    game_elements.push_back(std::dynamic_pointer_cast<drawable>(paddle1));
    game_elements.push_back(std::dynamic_pointer_cast<drawable>(paddle2));
    game_elements.push_back(std::dynamic_pointer_cast<drawable>(ball1));

    collision_elements.push_back(std::dynamic_pointer_cast<boxcollision>(paddle1));
    collision_elements.push_back(std::dynamic_pointer_cast<boxcollision>(paddle2));
    collision_elements.push_back(std::dynamic_pointer_cast<boxcollision>(ball1));
}

int main(void)
{
    InitWindow(1280, 720, "Mein kleines Spiel");
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
