#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character(int windWidth, int windHeight) : m_windowWidth(windWidth),
                                                      m_windowHeight(windHeight)
{
    _width = _character_texture.width / (float)_maxFrames;
    _height = _character_texture.height;
}

Vector2 Character::GetScreenPosition()
{
    return Vector2{
        static_cast<float>(m_windowWidth) / 2.0f - _characterScaleMultiplier * (0.5f * _width),
        static_cast<float>(m_windowHeight) / 2.0f - _characterScaleMultiplier * (0.5f * _height)};
}

void Character::TakeDamage(float damage)
{
    m_health -= damage;
    if (m_health <= 0.f)
        SetAlive(false);
        
}

void Character::Tick(float deltatime)
{
    if (!GetAlive())
        return;

    BaseCharacter::Tick(deltatime);

    // Movement
    if (IsKeyDown(KEY_A))
        _velocity.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        _velocity.x += 1.0f;
    if (IsKeyDown(KEY_W))
        _velocity.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        _velocity.y += 1.0f;

    // Switch origin base on character facing direction
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (_rightLeft > 0.f) // facing right
    {
        origin = {0.f, m_weapon.height * _characterScaleMultiplier};
        offset = {35.f, 55.f};
        m_weaponCollisionRect = {
            GetScreenPosition().x + offset.x,
            GetScreenPosition().y + offset.y - m_weapon.height * _characterScaleMultiplier,
            m_weapon.width * _characterScaleMultiplier,
            m_weapon.height * _characterScaleMultiplier};

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
        // rotation = 35.f;
    }
    else // facing left
    {
        origin = {m_weapon.width * _characterScaleMultiplier, m_weapon.height * _characterScaleMultiplier};
        offset = {25.f, 55.f};
        m_weaponCollisionRect = {
            GetScreenPosition().x + offset.x - m_weapon.width * _characterScaleMultiplier,
            GetScreenPosition().y + offset.y - m_weapon.height * _characterScaleMultiplier,
            m_weapon.width * _characterScaleMultiplier,
            m_weapon.height * _characterScaleMultiplier};

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
        // rotation = -35.f;
    }

    //* Draw Sword
    Rectangle source{0.f, 0.f, static_cast<float>(m_weapon.width) * _rightLeft, static_cast<float>(m_weapon.height)};
    Rectangle destination{GetScreenPosition().x + offset.x, GetScreenPosition().y + offset.y, m_weapon.width * _characterScaleMultiplier, m_weapon.height * _characterScaleMultiplier};
    DrawTexturePro(m_weapon, source, destination, origin, rotation, WHITE);

    DrawRectangleLines(
        m_weaponCollisionRect.x,
        m_weaponCollisionRect.y,
        m_weaponCollisionRect.width,
        m_weaponCollisionRect.height,
        RED);
}
