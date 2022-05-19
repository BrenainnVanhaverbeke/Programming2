#pragma once
#include "Vector2f.h"

class Character;

class MovementBehaviour
{
public:
	MovementBehaviour(const Vector2f acceleration);
	virtual ~MovementBehaviour() = default;

	virtual void Update(float elapsedSec, Character& character) = 0;
	virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) = 0;
	virtual void Move(float elapsedSec, Character& character) = 0;

protected:
	const Vector2f m_Acceleration;

	Vector2f m_Velocity;
};

