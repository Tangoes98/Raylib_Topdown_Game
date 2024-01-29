#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::UndoMovement()
{
    _characterWorldPos = _characterPosAtLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        GetScreenPosition().x,
        GetScreenPosition().y,
        _width * _characterScaleMultiplier,
        _height * _characterScaleMultiplier};
}

void BaseCharacter::Tick(float deltaTime)
{
    _characterPosAtLastFrame = _characterWorldPos;

    // Update animaiton frame
    _runningTime += deltaTime;
    if (_runningTime >= _updateTime)
    {
        _frame++;
        _runningTime = 0.f;
        if (_frame > _maxFrames)
            _frame = 0;
    }

    // Check character facing direction
    if (Vector2Length(_velocity) != 0.0f)
    {
        _characterWorldPos = Vector2Add(_characterWorldPos, Vector2Scale(Vector2Normalize(_velocity), _speed));
        _velocity.x < 0.f ? _rightLeft = -1.f : _rightLeft = 1.f;
        _character_texture = _character_run;
    }
    else
    {
        _character_texture = _character_idle;
    }
    _velocity = {};

    // Draw the Character
    Rectangle source{_frame * _width, 0.f, _rightLeft * _width, _height};
    Rectangle destination{
        GetScreenPosition().x,
        GetScreenPosition().y,
        _characterScaleMultiplier * _width,
        _characterScaleMultiplier * _height};
    DrawTexturePro(_character_texture, source, destination, Vector2{}, 0.f, WHITE);
}
