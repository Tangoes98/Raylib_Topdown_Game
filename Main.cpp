#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>
#include "Score.h"

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
        Vector2{800.f, 300.f},
        LoadTexture("Asset/CharacterSprite/goblin_idle_spritesheet.png"),
        LoadTexture("Asset/CharacterSprite/goblin_run_spritesheet.png")};

    Enemy _slime{
        Vector2{500.f, 700.f},
        LoadTexture("Asset/CharacterSprite/slime_idle_spritesheet.png"),
        LoadTexture("Asset/CharacterSprite/slime_run_spritesheet.png")};

    Enemy *_enemies[]{
        &_goblin,
        &_slime};

    Score _score{};

    for (auto enemy : _enemies)
    {
        enemy->SetTarget(&_knight);
        enemy->SetScore(&_score);
    }

    SetTargetFPS(60);

    //* ========== UPDATE STARTS HERE ==========

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

        // Draw health
        if (!_knight.GetAlive()) // Player is dead
        {
            DrawText("GameOver!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // player is alive
        {
            std::string playerHealth = "Health: ";
            playerHealth.append(std::to_string(_knight.GetHealth()), 0, 5);
            DrawText(playerHealth.c_str(), 55.f, 45.f, 40, RED);

            std::string playerScore = "Score: ";
            playerScore.append(std::to_string(_score.GetScore()));
            DrawText(playerScore.c_str(), 55.f, 300.f, 40, RED);
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

        // Update enemy actions
        for (auto enemy : _enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : _enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), _knight.GetWeaponCollisionRect()))
                    enemy->SetAlive(false);
            }
        }

        EndDrawing();
    }
    CloseWindow();
}
