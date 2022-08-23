#pragma once
#include "Projectile.h"

class Axe final : public Projectile
{
public:
	explicit Axe(const Point2f& origin, const Rectf& boundaries, bool isFlipped, int zIndex);
	Axe& operator=(const Axe& rhs) = delete;
	Axe& operator=(Axe&& rhs) = delete;
	Axe(const Axe& other) = delete;
	Axe(Axe&& other) = delete;

	virtual bool IsFlaggedForDeletion() const override;
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

private:
	const static int m_Damage{ 20 };
	const float m_RotationSpeed;

	// Inherited via Projectile
	virtual Sprite* CreateSprite() override;
	virtual ProjectileTag GetProjectileTag() const override;
};

