#include "pch.h"
#include "Character.h"
#include "Sprite.h"
#include "MovementBehaviour.h"

Character::Character(Transform transform, Sprite* sprite, float width, float height, const Vector2f& acceleration)
	: GameObject(transform)
	, m_pSprite{ sprite }
	, m_Width{ width }
	, m_Height{ height }
	, m_Acceleration{ acceleration }
	, m_Velocity{}
	, m_pMovementBehaviour{ nullptr }
{
}

Character::~Character()
{
	delete m_pSprite;
	m_pSprite = nullptr;
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

Vector2f& Character::GetVelocity() const
{
	return m_pMovementBehaviour->GetVelocity();
}