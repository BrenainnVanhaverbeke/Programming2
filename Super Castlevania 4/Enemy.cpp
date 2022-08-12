#include "pch.h"
#include "Enemy.h"
#include "Sprite.h"

Enemy::Enemy(Transform transform, Sprite* sprite, float width, float height, const Vector2f& acceleration, const float activationDistance)
	: Character(transform, sprite, width, height, acceleration)
	, m_ActivationDistance{ activationDistance }
	, m_IsActive{ false }
{
}
