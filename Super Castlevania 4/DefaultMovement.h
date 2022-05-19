#pragma once
#include "MovementBehaviour.h"
class DefaultMovement : public MovementBehaviour
{
public:
	// Inherited via MovementBehaviour
	virtual void Update(float elapsedSec, Character& character) override;
	virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) override;
	virtual void Move(float elapsedSec, Character& character) override;
};

