#include "raylib.h"
#include "raymath.h"

int main()
{
    const int _windowWidth{384};
    const int _windowHeight{384};

    InitWindow(_windowWidth, _windowHeight, "MAIN_GAME");

    Texture2D _map = LoadTexture("Asset/TileMap/TileMap24x24_16_BG.png");
    Vector2 _mapPos{0.0f, 0.0f};
    float _speed{4.0f};

    Texture2D _character = LoadTexture("Asset/CharacterSprite/knight_idle_spritesheet.png");
    float _characterScaleMultiplier = 4.0f;
    Vector2 _characterPos{
        (float)_windowWidth / 2.0f - _characterScaleMultiplier * (0.5f * (float)_character.width / 6.0f),
        (float)_windowHeight / 2.0f - _characterScaleMultiplier * (0.5f * (float)_character.height)};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Camera Movement
        Vector2 direction{};
        if (IsKeyDown(KEY_A))
            direction.x -= 1.0f;
        if (IsKeyDown(KEY_D))
            direction.x += 1.0f;
        if (IsKeyDown(KEY_W))
            direction.y -= 1.0f;
        if (IsKeyDown(KEY_S))
            direction.y += 1.0f;
        if (Vector2Length(direction) != 0.0f)
        {
            _mapPos = Vector2Subtract(_mapPos, Vector2Scale(Vector2Normalize(direction), _speed));
        }

        // Draw map
        DrawTextureEx(_map, _mapPos, 0.0f, 4.0f, WHITE);

        // Draw the character
        Rectangle source{0.f, 0.f, (float)_character.width / 6.0f, (float)_character.height};
        Rectangle destination{
            _characterPos.x,
            _characterPos.y,
            _characterScaleMultiplier * (float)_character.width / 6.0f,
            _characterScaleMultiplier * (float)_character.height};

        DrawTexturePro(_character, source, destination, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
    CloseWindow();
}
