#include "pch.h"
#include "Bat.h"
#include "SinewaveMovement.h"
#include "Sprite.h"
#include "utils.h"

Bat::Bat(Transform transform, Sprite* sprite, int zIndex)
	: Character(transform, sprite, new SinewaveMovement(50, 25.0f, 2, transform.positionY, false), 16.0f, 16.0f, zIndex)
{
}

void Bat::Update(float elapsedSec)
{
	Rectf boundaries{ 0, 0, 1000, 1000 };
	m_pMovementBehaviour->Update(elapsedSec, m_Transform, GetShape(), boundaries);
	m_pSprite->Update(elapsedSec);
}

void Bat::Draw(int zIndex) const
{
	if (zIndex == m_ZIndex)
		m_pSprite->Draw(m_Transform, 0 < m_pMovementBehaviour->GetVelocity().x);
}

void Bat::CheckOverlap(const Rectf& overlappingShape)
{
}

bool Bat::IsOverlapping(const Rectf& overlappingShape)
{
	return false;
}
