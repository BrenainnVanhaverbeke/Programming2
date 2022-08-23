#include "pch.h"
#include "Projectile.h"
#include "Sprite.h"
#include "utils.h"
#include "ProjectileTag.h"
#include <iostream>

Projectile::Projectile(const Transform& transform, const Vector2f& initialVelocity, const Vector2f& acceleration, Sprite* sprite, ProjectileTag tag, const Rectf& boundaries, float width, float height, bool isFriendly, bool isFlipped, int damage, int zIndex)
	: GameObject(transform, zIndex)
	, m_Boundaries{ boundaries }
	, m_Acceleration{ acceleration }
	, m_Velocity{ initialVelocity }
	, m_pSprite{ sprite }
	, m_FlaggedForDeletion{ false }
	, m_Width{ width }
	, m_Height{ height }
	, m_ProjectileTag{ tag }
	, m_IsFriendly{ isFriendly }
	, m_Damage{ damage }
	, m_ImmuneList{}
	, m_IsFlipped{ isFlipped }
{
	if (isFlipped)
	{
		m_Transform.positionX -= m_Width;
		m_Velocity.x *= -1;
	}
}

Projectile::Projectile(const Point2f& origin, const Vector2f& initialVelocity, const Vector2f& acceleration, Sprite* sprite, ProjectileTag tag, const Rectf& boundaries, float width, float height, bool isFriendly, bool isFlipped, int damage, int zIndex)
	: Projectile(Transform{ origin, 0, 1.0f }, initialVelocity, acceleration, sprite, tag, boundaries, width, height, isFriendly, isFlipped, damage, zIndex)
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
	m_Transform.SetTranslation(m_Transform.GetTranslation() + (m_Velocity * elapsedSec));
}

void Projectile::Draw(int zIndex) const
{
	if (m_ZIndex == zIndex)
		m_pSprite->Draw(m_Transform, m_IsFlipped);
}

void Projectile::DrawDebug(int zIndex) const
{
	if (m_ZIndex == zIndex)
	{
		utils::DrawRect(GetShape());
		utils::DrawPoint(m_Transform.GetTranslation());
	}
}

void Projectile::CheckOverlap(const Rectf& overlappingShape)
{
}

bool Projectile::IsOverlapping(const Rectf& overlappingShape)
{
	return utils::IsOverlapping(overlappingShape, GetShape());
}

bool Projectile::IsOverlapping(const std::vector<Point2f>& overlappingShape)
{
	return utils::IsPointInPolygon(GetShape().GetCenter(), overlappingShape);
}

void Projectile::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

bool Projectile::IsFriendly()
{
	return m_IsFriendly;
}

bool Projectile::IsFlaggedForDeletion() const
{
	return m_FlaggedForDeletion;
}

Rectf Projectile::GetShape() const
{
	return Rectf{ m_Transform.positionX, m_Transform.positionY, m_Width, m_Height };
}

int Projectile::GetDamage()
{
	return m_Damage;
}

void Projectile::AddToImmuneList(int id)
{
	m_ImmuneList.push_back(id);
}

std::vector<int> Projectile::GetImmuneList() const
{
	return m_ImmuneList;
}