#include "raylib.h"
#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::UndoMovement()
{
    _characterWorldPos = _characterPosAtLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        _characterScreenPos.x,
        _characterScreenPos.y,
        _width * _characterScaleMultiplier,
        _height * _characterScaleMultiplier};
}
