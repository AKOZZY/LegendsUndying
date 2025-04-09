#include "raylib.h"
#include "Game.h"

#include <iostream>
#include <fstream>

int main(void)
{
    // Window settings
    const int screenWidth{ 800 };
    const int screenHeight{ 800 };

    InitWindow(screenWidth, screenHeight, "LegendsUndying");

    // Set game framerate
    SetTargetFPS(144);

    // Create game instance
    Game* game = new Game();

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