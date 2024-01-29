#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int windWidth, int windHeight);
    virtual void Tick(float deltatime) override;
    virtual Vector2 GetScreenPosition() override;

private:
    int m_windowWidth;
    int m_windowHeight;
    Texture2D m_weapon { LoadTexture("Asset/CharacterSprite/weapon_sword.png")};
    Rectangle m_weaponCollisionRect;
};

#endif