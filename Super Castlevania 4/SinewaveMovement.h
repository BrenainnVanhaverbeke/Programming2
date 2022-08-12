#pragma once
#include "MovementBehaviour.h"
class SinewaveMovement :
    public MovementBehaviour
{
    // Inherited via MovementBehaviour
    virtual void Update(float elapsedSec, Character& character, const Rectf& boundaries) override;
    virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) override;
    virtual void Move(float elapsedSec, Transform& character) override;
};

