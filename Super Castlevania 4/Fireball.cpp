#include "pch.h"
#include "Fireball.h"
#include "Sprite.h"
#include "ProjectileTag.h"

Fireball::Fireball(const Point2f& origin, const Rectf& boundaries, bool isFlipped, int zIndex)
	: Projectile
	(
		origin,
		Vector2f{ 50.0f, 0 },
		Vector2f{},
		CreateSprite(),
		ProjectileTag::fireball,
		boundaries,
		9.0f,
		5.0f,
		false,
		isFlipped,
		10,
		zIndex
	)
	, m_HasHit{ false }
{
}

void Fireball::Update(float elapsedSec)
{
	Projectile::Update(elapsedSec);
	m_pSprite->Update(elapsedSec);
}

bool Fireball::IsFlaggedForDeletion() const
{
	const Point2f& position{ m_Transform.GetTranslation() };
	return m_HasHit || ((position.x < (m_Boundaries.left - m_Width)
		|| m_Boundaries.GetBottomRight().x < position.x));
}

ProjectileTag Fireball::GetProjectileTag() const
{
	return m_ProjectileTag;
}

Sprite* Fireball::CreateSprite()
{
	const Rectf sourceRect{ 56.0f, 577.0f, 9.0f, 5.0f };
	return new Sprite("Enemies.png", sourceRect, 2, 1, 4);
}
