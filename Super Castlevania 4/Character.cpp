#include "pch.h"
#include "Character.h"
#include "Sprite.h"
#include "MovementBehaviour.h"

Character::Character(Transform transform, Sprite* sprite, MovementBehaviour* movement, float width, float height, int zIndex)
	: GameObject(transform, zIndex)
	, m_pSprite{ sprite }
	, m_Width{ width }
	, m_Height{ height }
	, m_pMovementBehaviour{ movement }
{
}

Character::~Character()
{
	delete m_pSprite;
	delete m_pMovementBehaviour;
	m_pSprite = nullptr;
	m_pMovementBehaviour = nullptr;
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