#include "pch.h"
#include "ClackityBoneManMovement.h"

ClackityBoneManMovement::ClackityBoneManMovement(const Vector2f& acceleration)
	: MovementBehaviour(acceleration)
	, m_HorizontalSpeed{ 75.0f }
	, m_JumpForce{ 325.0f }
{

}

void ClackityBoneManMovement::Update(float elapsedSec, Transform& transform, const Rectf& shape, const Rectf& boundaries)
{
}

void ClackityBoneManMovement::UpdateVelocity(float elapsedSec, const Uint8* pKeysState)
{
}

void ClackityBoneManMovement::Move(float elapsedSec, Transform& transform)
{
}
