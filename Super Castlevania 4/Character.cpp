#include "pch.h"
#include "Character.h"

Character::Character(Transform transform, float width, float height, const Vector2f& acceleration)
	: GameObject(transform)
	, m_Width{ width }
	, m_Height{ height }
	, m_Acceleration{ acceleration }
	, m_Velocity{}
{
}

Character::~Character()
{
}

Rectf Character::GetShape() const
{
	return Rectf{
		m_Transform.positionX,
		m_Transform.positionY,
		m_Width,
		m_Height
	};
}

Vector2f& Character::GetVelocity()
{
	return m_Velocity;
}