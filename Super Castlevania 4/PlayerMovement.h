#pragma once
#include "MovementBehaviour.h"

class Character;

class PlayerMovement : public MovementBehaviour
{
public:
	PlayerMovement(const Vector2f& acceleration);
	virtual ~PlayerMovement() = default;

	// Inherited via MovementBehaviour
	virtual void Update(float elapsedSec, Character& character, const Rectf& boundaries) override;

private:
	const float m_HorizontalSpeed;

	virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) override;
	virtual void Move(float elapsedSec, Transform& transform) override;
	void Clamp(Transform& m_Transform, const Rectf& boundaries, float characterWidth);
	void UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState, Vector2f& velocity);
	void UpdateVerticalVelocity(float elapsedSec, const Uint8* pKeysState, Vector2f& velocity);
};