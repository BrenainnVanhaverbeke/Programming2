#pragma once
#include "Projectile.h"
class Fireball : public Projectile
{
public: 	
	explicit Fireball(const Point2f& origin, const Rectf& boundaries, bool isFlipped, int zIndex);
	Fireball(const Fireball& other) = delete;
	Fireball(Fireball&& other) = delete;
	Fireball& operator=(const Fireball& other) = delete;
	Fireball& operator=(Fireball&& other) = delete;
	virtual ~Fireball() = default;

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;

	// Inherited via Projectile
	virtual bool IsFlaggedForDeletion() const override;
	virtual ProjectileTag GetProjectileTag() const override;
	virtual Sprite* CreateSprite() override;

private:
	bool m_HasHit;
};