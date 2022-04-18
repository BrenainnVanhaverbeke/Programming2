#pragma once
#include "Vector2f.h"
#include "GameObject.h"

class Sprite;

class Projectile : public GameObject
{
public:
	explicit Projectile(const Point2f& origin, const Vector2f& acceleration, Sprite* sprite);
	explicit Projectile(const Transform& transform, const Vector2f& acceleration, Sprite* sprite);
	virtual ~Projectile();

protected:
	Vector2f m_Acceleration;
	Vector2f m_Velocity;
	Sprite* m_pSprite;

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;
};

