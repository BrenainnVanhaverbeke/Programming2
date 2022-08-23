#pragma once
#include "MovementBehaviour.h"
class NoMovement : public MovementBehaviour
{
public:
	NoMovement();

	// Inherited via MovementBehaviour
	virtual void Update(float elapsedSec, Transform& transform, const Rectf& shape, const Rectf& boundaries) override;
	virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) override;
	virtual void Move(float elapsedSec, Transform& transform) override;
};

