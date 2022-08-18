#pragma once
#include "MovementBehaviour.h"
class SinewaveMovement final : public MovementBehaviour
{

public:
    SinewaveMovement(float xAcceleration, float amplitude, float frequency, float intercept, bool isMovingLeft);

    // Inherited via MovementBehaviour
    virtual void Update(float elapsedSec, Transform& transform, const Rectf& shape, const Rectf& boundaries) override;
    virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) override;
    virtual void Move(float elapsedSec, Transform& transform) override;

private:
    const float m_Intercept;
    float m_Amplitude;
    float m_Frequency;
};