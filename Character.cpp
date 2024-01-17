#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character()
{
    _width = _character_texture.width / (float)_maxFrames;
    _height = _character_texture.height;
}

void Character::SetCharacterPos(int winWidth, int winHeight)
{
    _characterPos = {
        (float)winWidth / 2.0f - _characterScaleMultiplier * (0.5f * _width),
        (float)winHeight / 2.0f - _characterScaleMultiplier * (0.5f * _height)};
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
    Rectangle source{_frame * _width, 0.f, _rightLeft * _width, _height};
    Rectangle destination{
        _characterPos.x,
        _characterPos.y,
        _characterScaleMultiplier * _width,
        _characterScaleMultiplier * _height};
    DrawTexturePro(_character_texture, source, destination, Vector2{}, 0.f, WHITE);
}
