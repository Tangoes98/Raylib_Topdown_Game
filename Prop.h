#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 characterPos);
    Rectangle GetCollisionRec(Vector2 character);
private:
    Vector2 m_worldPos{};
    Texture2D m_texture{};
    float m_scale{4.f};
};