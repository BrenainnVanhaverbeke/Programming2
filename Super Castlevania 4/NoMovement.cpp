#include "pch.h"
#include "NoMovement.h"

NoMovement::NoMovement()
	: MovementBehaviour{ Vector2f{} }
{
}

void NoMovement::Update(float elapsedSec, Transform& transform, const Rectf& shape, const Rectf& boundaries, const Vector2f& forcedMovement)
{
}

void NoMovement::UpdateVelocity(float elapsedSec, const Uint8* pKeysState)
{
}

void NoMovement::Move(float elapsedSec, Transform& transform)
{
}
