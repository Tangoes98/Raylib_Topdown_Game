#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"
#include "Score.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
    virtual void Tick(float deltatime) override;
    void SetTarget(Character *character) { m_target = character; }
    void SetScore(Score *score) { m_score = score; }
    virtual Vector2 GetScreenPosition() override;

private:
    Character *m_target;
    float m_damagePerSecOverlapingPlayer{50.f};
    float m_radius{20.f};
    Vector2 m_originalPosition{};
    Score *m_score;
};
