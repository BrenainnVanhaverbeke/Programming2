#include "pch.h"
#include "Projectile.h"
#include "Sprite.h"

Projectile::Projectile(const Transform& transform, const Vector2f& acceleration, Sprite* sprite)
	: GameObject(transform)
	, m_Acceleration{ acceleration }
	, m_Velocity{}
	, m_pSprite{ sprite }
{
}

Projectile::Projectile(const Point2f& origin, const Vector2f& acceleration, Sprite* sprite)
	: Projectile(Transform{ origin, 0, 1.0f }, acceleration, sprite)
{
}

Projectile::~Projectile()
{
	delete m_pSprite;
	m_pSprite = nullptr;
}

void Projectile::Update(float elapsedSec)
{
	m_Velocity += (m_Acceleration * elapsedSec);
}

void Projectile::Draw() const
{
	m_pSprite->Draw(m_Transform);
}

void Projectile::CheckOverlap(const Rectf& overlappingShape)
{
}

bool Projectile::IsOverlapping(const Rectf& overlappingShape)
{
	return false;
}
