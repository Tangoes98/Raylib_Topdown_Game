#include "Prop.h"
#include "raylib.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : m_worldPos(pos),
                                         m_texture(tex)
{
}

void Prop::Render(Vector2 characterPos)
{
    Vector2 screenPos{Vector2Subtract(m_worldPos, characterPos)};
    DrawTextureEx(m_texture, screenPos, 0.f, m_scale, WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 characterPos)
{
    Vector2 screenPos{Vector2Subtract(m_worldPos, characterPos)};
    return Rectangle
    {
        screenPos.x,
            screenPos.y,
            m_texture.width *m_scale,
            m_texture.height *m_scale,
    };
}
