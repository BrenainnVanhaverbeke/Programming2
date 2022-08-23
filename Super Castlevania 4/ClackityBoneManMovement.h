#pragma once
#include "MovementBehaviour.h"
class ClackityBoneManMovement : public MovementBehaviour
{
public:
	explicit ClackityBoneManMovement(const Vector2f& acceleration);

	// Inherited via MovementBehaviour
	virtual void Update(float elapsedSec, Transform& transform, const Rectf& shape, const Rectf& boundaries) override;
	virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) override;
	virtual void Move(float elapsedSec, Transform& transform) override;

private:
	float m_HorizontalSpeed;
	float m_JumpForce;
};

