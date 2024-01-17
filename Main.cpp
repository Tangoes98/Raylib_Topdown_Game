#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 GetWorldPos() { return _characterWorldPos; }
    void SetCharacterPos(int winWidth, int winHeight);
    void Tick(float delatime);

private:
    Texture2D _character_texture{LoadTexture("Asset/CharacterSprite/knight_idle_spritesheet.png")};
    Texture2D _character_idle{LoadTexture("Asset/CharacterSprite/knight_idle_spritesheet.png")};
    Texture2D _character_run{LoadTexture("Asset/CharacterSprite/knight_run_spritesheet.png")};
    Vector2 _characterPos{0.f, 0.f};
    Vector2 _characterWorldPos{0.f, 0.f};
    float _characterScaleMultiplier = 4.0f;
    // 1: facing right, -1: facing left
    float _rightLeft{1.f};

    // Animation Variables
    float _runningTime{};
    int _frame{};
    const int _maxFrames{6};
    const float _updateTime{1.f / 12.f};

    const float _speed{4.f};
};

void Character::SetCharacterPos(int winWidth, int winHeight)
{
    _characterPos = {
        (float)winWidth / 2.0f - _characterScaleMultiplier * (0.5f * (float)_character_texture.width / 6.0f),
        (float)winHeight / 2.0f - _characterScaleMultiplier * (0.5f * (float)_character_texture.height)};
}

void Character::Tick(float delatime)
{
    // Movement
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
        _characterWorldPos = Vector2Add(_characterWorldPos, Vector2Scale(Vector2Normalize(direction), _speed));
        direction.x < 0.f ? _rightLeft = -1.f : _rightLeft = 1.f;
        _character_texture = _character_run;
    }
    else
    {
        _character_texture = _character_idle;
    }

    // Update animaiton frame
    _runningTime += delatime;
    if (_runningTime >= _updateTime)
    {
        _frame++;
        _runningTime = 0.f;
        if (_frame > _maxFrames)
            _frame = 0;
    }

    // Draw the Character
    Rectangle source{_frame * (float)_character_texture.width / 6.0f, 0.f, _rightLeft * (float)_character_texture.width / 6.0f, (float)_character_texture.height};
    Rectangle destination{
        _characterPos.x,
        _characterPos.y,
        _characterScaleMultiplier * (float)_character_texture.width / 6.0f,
        _characterScaleMultiplier * (float)_character_texture.height};
    DrawTexturePro(_character_texture, source, destination, Vector2{}, 0.f, WHITE);
}


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

