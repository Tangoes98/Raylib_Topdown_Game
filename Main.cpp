#include "raylib.h"
#include "raymath.h"
#include "Character.h"


int main()
{
    const int _windowWidth{384};
    const int _windowHeight{384};

    InitWindow(_windowWidth, _windowHeight, "MAIN_GAME");

    Texture2D _map = LoadTexture("Asset/TileMap/TileMap24x24_16_BG.png");
    Vector2 _mapPos{0.0f, 0.0f};

    Character _knight;
    _knight.SetCharacterPos(_windowWidth, _windowHeight);


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        _mapPos = Vector2Scale(_knight.GetWorldPos(), -1.f);


        // Draw map
        DrawTextureEx(_map, _mapPos, 0.0f, 4.0f, WHITE);

        _knight.Tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
}

