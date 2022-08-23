#include "pch.h"
#include "SinewaveMovement.h"

SinewaveMovement::SinewaveMovement(float xAcceleration, float amplitude, float frequency, float intercept, bool isMovingLeft)
	: MovementBehaviour(Vector2f{isMovingLeft ? -xAcceleration : xAcceleration, 0})
	, m_Amplitude{ amplitude }
	, m_Frequency{ frequency }
	, m_Intercept{ intercept }
{
}

void SinewaveMovement::Update(float elapsedSec, Transform& transform, const Rectf& shape, const Rectf& boundaries, const Vector2f& forcedMovement)
{
	UpdateVelocity(elapsedSec, nullptr);
	Move(elapsedSec, transform);
}

void SinewaveMovement::UpdateVelocity(float elapsedSec, const Uint8* pKeysState)
{
	m_Velocity = m_Acceleration * elapsedSec;
}

void SinewaveMovement::Move(float elapsedSec, Transform& transform)
{
	transform.positionX += m_Velocity.x;
	transform.positionY = m_Amplitude * sinf(transform.positionX * m_Frequency * float(M_PI / 180)) + m_Intercept;
}
