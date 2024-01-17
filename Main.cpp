#include "raylib.h"

int main()
{
    const int _windowWidth{384};
    const int _windowHeight{384};

    InitWindow(_windowWidth, _windowHeight, "MAIN_GAME");

    Texture2D _map = LoadTexture("Asset/TileMap/TileMap24x24_16_BG.png");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 mapPos{0.0, 0.0};
        DrawTextureEx(_map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    CloseWindow();
}
