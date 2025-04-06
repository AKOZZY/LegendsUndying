#include "raylib.h"
#include "Game.h"

#include <iostream>
#include <fstream>

int main(void)
{
    // Things to work on:
    // Create saving and loading system
    // Create wave spawner system

    // Added to git

    // Window settings
    const int screenWidth{ 800 };
    const int screenHeight{ 800 };

    InitWindow(screenWidth, screenHeight, "LegendsUndying");

    // Set game framerate
    SetTargetFPS(144);

    // Create game instance
    Game* game = new Game();

    // Create save
    std::ofstream LU_SaveData("lu_savedata.txt");

    LU_SaveData << "data" << "\n";
    //LU_SaveData << 3;

    LU_SaveData.close();

    game->Start();

    // Game loop
    while (!WindowShouldClose() && !game->hasQuitGame)
    {
        switch (game->gameCurrentState)
        {

        case(MAIN_MENU):

            game->UpdateMainMenu();

            BeginDrawing();
            BeginMode2D(game->GetCamera());

            ClearBackground(BLACK);
            game->RenderMainMenu();

            EndMode2D();
            EndDrawing();

            break;
        case(IN_GAME):

            game->UpdateGameplay();
            game->Input();

            BeginDrawing();
            BeginMode2D(game->GetCamera());

            ClearBackground(BLACK);
            game->Render();

            EndMode2D();
            game->RenderUI();
            EndDrawing();
           
            break;
        default:

            break;
        }
    }
    CloseWindow();
    delete(game);

    return 0;
}