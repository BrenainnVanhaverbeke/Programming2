#pragma once
#include "Vector2f.h"

class MovementBehaviour
{
public:
	MovementBehaviour(const Vector2f& acceleration);
	virtual ~MovementBehaviour() = default;

	virtual void Update(float elapsedSec, Transform& transform, const Rectf& shape, const Rectf& boundaries, const Vector2f & forcedMovement = Vector2f{}) = 0;
	virtual void Jump(); 
	virtual Vector2f& GetVelocity() final;
	virtual void Knockback(float force);

protected:
	virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) = 0;
	virtual void Move(float elapsedSec, Transform& transform) = 0;

	const Vector2f m_Acceleration;
	Vector2f m_Velocity;
};