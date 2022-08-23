#include "pch.h"
#include "Cross.h"
#include "ProjectileTag.h"
#include "Sprite.h"
#include <iostream>

Cross::Cross(const Point2f& origin, const Rectf& boundaries, bool isFlipped, int zIndex)
	: Projectile
	(
		origin,
		Vector2f{ 100.0f, 0 },
		Vector2f{},
		CreateSprite(),
		ProjectileTag::cross,
		boundaries,
		15.0f,
		15.0f,
		true,
		isFlipped,
		30,
		zIndex
	)
	, m_RotationSpeed{ -720.0f * (isFlipped ? -1 : 1) }
	, m_HasBounced{ false }
{
}

bool Cross::IsFlaggedForDeletion() const
{
	const Point2f& position{ m_Transform.GetTranslation() };
	return m_HasBounced
		&& (position.x < (m_Boundaries.left - m_Width) || m_Boundaries.GetBottomRight().x < position.x);
}

ProjectileTag Cross::GetProjectileTag() const
{
	return ProjectileTag::cross;
}

Sprite* Cross::CreateSprite()
{
	const Rectf sourceRect{ 127.0f, 17.0f, 16.0f, 16.0f };
	return new Sprite("Items.png", sourceRect);
}

void Cross::Update(float elapsedSec)
{
	Projectile::Update(elapsedSec);
	m_Transform.angle += m_RotationSpeed * elapsedSec;
	const Point2f& position{ m_Transform.GetTranslation() };
	if (!m_HasBounced && (position.x < m_Boundaries.left || m_Boundaries.GetBottomRight().x - m_Width < position.x))
	{
		m_HasBounced = true;
		m_IsFlipped = !m_IsFlipped;
		m_RotationSpeed = -m_RotationSpeed;
		m_Velocity.x = -m_Velocity.x;
	}
}

void Cross::Draw(int zIndex) const
{
	if (zIndex == m_ZIndex)
		m_pSprite->DrawRotatedCenter(m_Transform, m_Width, m_Height, m_IsFlipped);
}