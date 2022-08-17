#pragma once
#include "Vector2f.h"

class Character;

class MovementBehaviour
{
public:
	MovementBehaviour(const Vector2f acceleration);
	virtual ~MovementBehaviour() = default;

	virtual void Update(float elapsedSec, Character& character, const Rectf& boundaries) = 0;
	virtual void Jump(); 
	virtual Vector2f& GetVelocity() final;

protected:
	virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) = 0;
	virtual void Move(float elapsedSec, Transform& character) = 0;

	const Vector2f m_Acceleration;
	Vector2f m_Velocity;
};