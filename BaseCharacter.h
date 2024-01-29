
#ifndef BASE_CHARACTER_H

#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 GetWorldPos() { return _characterWorldPos; }
    void UndoMovement();
    Rectangle GetCollisionRec();
    virtual Vector2 GetScreenPosition() = 0;
    virtual void Tick(float deltaTime);

protected:
    Texture2D _character_texture{LoadTexture("Asset/CharacterSprite/knight_idle_spritesheet.png")};
    Texture2D _character_idle{LoadTexture("Asset/CharacterSprite/knight_idle_spritesheet.png")};
    Texture2D _character_run{LoadTexture("Asset/CharacterSprite/knight_run_spritesheet.png")};
    Vector2 _characterWorldPos{0.f, 0.f};
    Vector2 _characterPosAtLastFrame{0.f, 0.f};
    float _characterScaleMultiplier = 4.0f;

    // 1: facing right, -1: facing left
    float _rightLeft{1.f};

    // Animation Variables
    float _runningTime{};
    int _frame{};
    int _maxFrames{6};
    float _updateTime{1.f / 12.f};
    float _speed{4.f};
    float _width{};
    float _height{};
    Vector2 _velocity{};

private:
};

#endif