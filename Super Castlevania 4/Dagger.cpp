#include "pch.h"
#include "Dagger.h"
#include "ProjectileTag.h"
#include "Sprite.h"
#include <iostream>

Dagger::Dagger(const Point2f& origin, const Rectf& boundaries, bool isFlipped, int zIndex)
	: Projectile(origin, Vector2f{ 150.0f, 0 }, Vector2f{}, CreateSprite(), ProjectileTag::dagger, boundaries, 16.0f, 4, true, isFlipped, 10, zIndex)
	, m_HasHit{ false }
{
}

bool Dagger::IsFlaggedForDeletion() const
{
	const Point2f& position{ m_Transform.GetTranslation() };
	return m_HasHit || (position.x < (m_Boundaries.left - m_Width) || m_Boundaries.GetBottomRight().x < position.x);
}

ProjectileTag Dagger::GetProjectileTag() const
{
	return ProjectileTag::dagger;
}

Sprite* Dagger::CreateSprite()
{
	const Rectf sourceRect{ 49.0f, 33.0f, 16.0f, 4.0f };
	return new Sprite("Items.png", sourceRect);
}

bool Dagger::IsOverlapping(const Rectf& overlappingShape)
{
	if (Projectile::IsOverlapping(overlappingShape))
	{
		m_HasHit = true;
		return true;
	}
	return false;
}

bool Dagger::IsOverlapping(const std::vector<Point2f>& overlappingShape)
{
	if (Projectile::IsOverlapping(overlappingShape))
	{
		m_HasHit = true;
		return true;
	}
	return false;
}
