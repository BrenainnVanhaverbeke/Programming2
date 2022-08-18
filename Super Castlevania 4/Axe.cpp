#include "pch.h"
#include "Axe.h"
#include "Sprite.h"
#include "ProjectileTag.h"

Axe::Axe(const Point2f& origin, bool isFlipped)
	: Projectile(Transform{ origin }, Vector2f{ 100.0f, 400.0f }, Vector2f{ 0, -980.0f }, CreateSprite(), ProjectileTag::axe, 15.0f, 15.0f, true, isFlipped)
	, m_RotationSpeed{ -720.0f * (isFlipped ? -1 : 1) }
{
}

Sprite* Axe::CreateSprite()
{
	const Rectf sourceRect{ 112.0f, 33.0f, 15.0f, 15.0f };
	return new Sprite("Items.png", sourceRect);
}

bool Axe::IsFlaggedForDeletion() const
{
	return m_Transform.positionY < m_Boundaries.bottom;
}

void Axe::Update(float elapsedSec)
{
	Projectile::Update(elapsedSec);
	m_Transform.angle += m_RotationSpeed * elapsedSec;
}

void Axe::Draw(int zIndex) const
{
	if (zIndex == m_ZIndex)
		m_pSprite->DrawRotatedCenter(m_Transform, m_Width, m_Height, m_Velocity.x < 0);
}

std::string Axe::GetProjectileTag() const
{
	return std::string();
}
