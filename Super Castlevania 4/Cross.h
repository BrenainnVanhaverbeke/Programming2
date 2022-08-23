#pragma once
#include "Projectile.h"
class Cross final : public Projectile
{
public:
	Cross(const Point2f& origin, const Rectf& boundaries, bool isFlipped, int zIndex);

	// Inherited via Projectile
	virtual bool IsFlaggedForDeletion() const override;
	virtual ProjectileTag GetProjectileTag() const override;
	virtual Sprite* CreateSprite() override;

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

private:
	bool m_HasBounced;
	float m_RotationSpeed;
};