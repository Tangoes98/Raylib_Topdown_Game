#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    const int _windowWidth{384};
    const int _windowHeight{384};
    // const int _windowWidth{640};
    // const int _windowHeight{640};

    InitWindow(_windowWidth, _windowHeight, "MAIN_GAME");

    Texture2D _map = LoadTexture("Asset/TileMap/TileMap24x24_16_BG.png");
    Vector2 _mapPos{0.0f, 0.0f};
    const float _mapScale = 4.f;

    Character _knight{_windowWidth, _windowHeight};

    // Create props
    Prop _props[2]{
        Prop{Vector2{500.f, 300.f}, LoadTexture("Asset/TileMap/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("Asset/TileMap/Log.png")},
    };

    // Create enemy
    Enemy _goblin{
        Vector2{},
        LoadTexture("Asset/CharacterSprite/goblin_idle_spritesheet.png"),
        LoadTexture("Asset/CharacterSprite/goblin_run_spritesheet.png")};

    _goblin.SetTarget(&_knight);





    

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        _mapPos = Vector2Scale(_knight.GetWorldPos(), -1.f);

        // Draw map
        DrawTextureEx(_map, _mapPos, 0.0f, 4.0f, WHITE);

        // Draw props
        for (auto prop : _props)
        {
            prop.Render(_knight.GetWorldPos());
        }

        // DrawText(TextFormat("MAP POS: %02f", _mapPos.x), 0, 0, 30, RED);
        // DrawText(TextFormat("MAP POS: %02f", _mapPos.y), 0, 30, 30, RED);

        _knight.Tick(GetFrameTime());

        // Check if inside map boundary
        if (_knight.GetWorldPos().x < 0.f ||
            _knight.GetWorldPos().y < 0.f ||
            _knight.GetWorldPos().x + _windowWidth > _map.width * _mapScale ||
            _knight.GetWorldPos().y + _windowHeight > _map.height * _mapScale)
        {
            _knight.UndoMovement();
        }

        // Collision Check
        for (auto prop : _props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRec(_knight.GetWorldPos()), _knight.GetCollisionRec()))
            {
                _knight.UndoMovement();
            }
        }

        _goblin.Tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
}
