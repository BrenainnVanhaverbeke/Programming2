#pragma once
#include "Projectile.h"
class Dagger : public Projectile
{
public:
	Dagger(const Point2f& origin, const Rectf& boundaries, bool isFlipped, int zIndex);

	// Inherited via Projectile
	virtual bool IsFlaggedForDeletion() const override;
	virtual ProjectileTag GetProjectileTag() const override;
	virtual Sprite* CreateSprite() override;

	// Inherited via IOverlappingObject
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const std::vector<Point2f>& overlappingShape) override;

private:
	bool m_HasHit;
};

