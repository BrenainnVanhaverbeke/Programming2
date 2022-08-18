#pragma once
#include "MovementBehaviour.h"

class PlayerMovement final : public MovementBehaviour
{
public:
	PlayerMovement(const Vector2f& acceleration);
	virtual ~PlayerMovement() = default;

	// Inherited via MovementBehaviour
	virtual void Update(float elapsedSec, Transform& transform, const Rectf& shape, const Rectf& boundaries) override;
	virtual void Jump() override;

private:
	const float m_JumpForce;
	const float m_HorizontalSpeed;

	virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) override;
	virtual void Move(float elapsedSec, Transform& transform) override;
	void Clamp(Transform& m_Transform, const Rectf& boundaries, float characterWidth);
	void UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState, Vector2f& velocity);
	void UpdateVerticalVelocity(float elapsedSec, const Uint8* pKeysState, Vector2f& velocity);
};