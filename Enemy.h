#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
    // Vector2 GetWorldPos() { return _characterWorldPos; }

    void Tick(float delatime);
    // void UndoMovement();

    // Rectangle GetCollisionRec();

private:
    // Vector2 _characterWorldPos{0.f, 0.f};
    // Texture2D _character_texture{LoadTexture("Asset/CharacterSprite/knight_idle_spritesheet.png")};
    // Texture2D _character_idle{LoadTexture("Asset/CharacterSprite/knight_idle_spritesheet.png")};
    // Texture2D _character_run{LoadTexture("Asset/CharacterSprite/knight_run_spritesheet.png")};
    // Vector2 _characterScreenPos{0.f, 0.f};
    // Vector2 _characterPosAtLastFrame{0.f, 0.f};
    // float _characterScaleMultiplier = 4.0f;

    // // 1: facing right, -1: facing left
    // float _rightLeft{1.f};

    // // Animation Variables
    // float _runningTime{};
    // int _frame{};
    // int _maxFrames{6};
    // float _updateTime{1.f / 12.f};
    // float _speed{4.f};
    // float _width{};
    // float _height{};
};
