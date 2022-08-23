#pragma once
#include "MovementBehaviour.h"
class ParabolicMovement : public MovementBehaviour
{
public:
	ParabolicMovement(float xVelocity, float yVelocity, bool isFlipped);
};