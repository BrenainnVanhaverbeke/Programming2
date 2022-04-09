#include "pch.h"
#include "Character.h"

Character::Character()
	: Character(Transform{ 0, 0, 0, 1.0f }, 0, 0)
{
}

Character::Character(float width, float height)
	: Character(Transform{ 0, 0, 0, 1.0f }, width, height)
{
}

Character::Character(Transform transform, float width, float height)
	: GameObject(transform)
	, m_Width{ width }
	, m_Height{ height }
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
