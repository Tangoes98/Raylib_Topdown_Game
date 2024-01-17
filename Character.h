#include "raylib.h"

class Character
{
public:
    Character();
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
    int _maxFrames{6};
    float _updateTime{1.f / 12.f};

    float _speed{4.f};

    float _width{};
    float _height{};
};