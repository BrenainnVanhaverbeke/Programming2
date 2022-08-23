#include "pch.h"
#include "ParabolicMovement.h"

ParabolicMovement::ParabolicMovement(float xVelocity, float yVelocity, bool isFlipped)
	: MovementBehaviour(Vector2f{ 0, G_GRAVITY })
{
}