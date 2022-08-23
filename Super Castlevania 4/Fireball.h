#pragma once
#include "Projectile.h"
class Fireball : public Projectile
{
public: 	
	Fireball(const Point2f& origin, const Rectf& boundaries, bool isFlipped, int zIndex);

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;

	// Inherited via Projectile
	virtual bool IsFlaggedForDeletion() const override;
	virtual ProjectileTag GetProjectileTag() const override;
	virtual Sprite* CreateSprite() override;

private:
	bool m_HasHit;
};