#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    _characterWorldPos = pos;
    _character_texture = idle_tex;
    _character_idle = idle_tex;
    _character_run = run_tex;
    _width = _character_texture.width / (float)_maxFrames;
    _height = _character_texture.height;
}

void Enemy::Tick(float delatime)
{
    _characterPosAtLastFrame = _characterWorldPos;

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
        _characterScreenPos.x,
        _characterScreenPos.y,
        _characterScaleMultiplier * _width,
        _characterScaleMultiplier * _height};
    DrawTexturePro(_character_texture, source, destination, Vector2{}, 0.f, WHITE);
}

// void Enemy::UndoMovement()
// {
//     _characterWorldPos = _characterPosAtLastFrame;
// }

// Rectangle Enemy::GetCollisionRec()
// {
//     return Rectangle{
//         _characterScreenPos.x,
//         _characterScreenPos.y,
//         _width * _characterScaleMultiplier,
//         _height * _characterScaleMultiplier};
// }
