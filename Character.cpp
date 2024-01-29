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

void Character::Tick(float deltatime)
{
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
}
