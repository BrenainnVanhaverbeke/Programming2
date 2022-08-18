#pragma once
#include "Projectile.h"

class Axe final : public Projectile
{
public:
	explicit Axe(const Point2f& origin, bool isFlipped);
	virtual ~Axe() = default;
	Axe& operator=(const Axe& rhs) = delete;
	Axe& operator=(Axe&& rhs) = delete;
	Axe(const Axe& other) = delete;
	Axe(Axe&& other) = delete;

	virtual bool IsFlaggedForDeletion() const override;
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

private:
	const float m_RotationSpeed;

	// Inherited via Projectile
	virtual Sprite* CreateSprite() override;
	virtual std::string GetProjectileTag() const override;
};

