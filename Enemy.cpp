#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    _characterWorldPos = pos;
    _character_texture = idle_tex;
    _character_idle = idle_tex;
    _character_run = run_tex;
    _width = _character_texture.width / (float)_maxFrames;
    _height = _character_texture.height;
    _speed = 3.f;
}

void Enemy::Tick(float deltatime)
{
    BaseCharacter::Tick(deltatime);

    _velocity = Vector2Subtract(m_target->GetScreenPosition(), GetScreenPosition());
}

Vector2 Enemy::GetScreenPosition()
{
    return Vector2Subtract(_characterWorldPos, m_target->GetWorldPos());
}