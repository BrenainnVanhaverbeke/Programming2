#include "pch.h"
#include "MovementBehaviour.h"

MovementBehaviour::MovementBehaviour(const Vector2f& acceleration)
	: m_Acceleration{ acceleration }
	, m_Velocity{ 0, 0 }
{
}

void MovementBehaviour::Jump()
{
}

Vector2f& MovementBehaviour::GetVelocity()
{
	return m_Velocity;
}