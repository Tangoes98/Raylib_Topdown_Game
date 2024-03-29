#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    _characterWorldPos = pos;
    m_originalPosition = pos;
    _character_texture = idle_tex;
    _character_idle = idle_tex;
    _character_run = run_tex;
    _width = _character_texture.width / (float)_maxFrames;
    _height = _character_texture.height;
    _speed = 2.f;
}

void Enemy::Tick(float deltatime)
{
    if (!GetAlive())
    {
        m_score->EarnScore();
        _characterWorldPos = Vector2{static_cast<float>(GetRandomValue(100, 800)), static_cast<float>(GetRandomValue(100, 800))};
        SetAlive(true);
        return;
    }

    BaseCharacter::Tick(deltatime);

    _velocity = Vector2Subtract(m_target->GetScreenPosition(), GetScreenPosition());

    if (Vector2Length(_velocity) < m_radius)
        _velocity = {};

    if (CheckCollisionRecs(m_target->GetCollisionRec(), GetCollisionRec()))
    {
        m_target->TakeDamage(m_damagePerSecOverlapingPlayer * deltatime);
    }
}

Vector2 Enemy::GetScreenPosition()
{
    return Vector2Subtract(_characterWorldPos, m_target->GetWorldPos());
}