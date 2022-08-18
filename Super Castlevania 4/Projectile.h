#pragma once
#include "Vector2f.h"
#include "GameObject.h"
#include "IOverlappingObject.h"

class Sprite;
enum class ProjectileTag;

class Projectile : public GameObject, public IOverlappingObject
{
public:
	explicit Projectile(const Point2f& origin, const Vector2f& initialVelocity, const Vector2f& acceleration, Sprite* sprite, ProjectileTag tag, float width, float height, bool isFriendly, bool isFlipped);
	explicit Projectile(const Transform& transform, const Vector2f& initialVelocity, const Vector2f& acceleration, Sprite* sprite, ProjectileTag tag, float width, float height, bool isFriendly, bool isFlipped);
	Projectile& operator=(const Projectile& rhs) = delete;
	Projectile& operator=(Projectile&& rhs) = delete;
	Projectile(const Projectile& other) = delete;
	Projectile(Projectile&& other) = delete;
	virtual ~Projectile();

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;
	
	// Inherited via IOverlappingObject
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;

	virtual void DrawDebug() const;
	virtual void SetBoundaries(const Rectf& boundaries);
	virtual bool IsFlaggedForDeletion() const = 0;
	virtual std::string GetProjectileTag() const = 0;

protected:
	const float m_Width;
	const float m_Height;
	const ProjectileTag m_ProjectileTag;
	const bool m_IsFriendly;

	Vector2f m_Acceleration;
	Vector2f m_Velocity;
	Sprite* m_pSprite;
	Rectf m_Boundaries;
	bool m_FlaggedForDeletion;

	virtual Sprite* CreateSprite() = 0;

	Rectf GetShape() const;
};

