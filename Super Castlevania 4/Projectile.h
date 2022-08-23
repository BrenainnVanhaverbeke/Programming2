#pragma once
#include "Vector2f.h"
#include "GameObject.h"
#include "IOverlappingObject.h"
#include <vector>

class Sprite;
enum class ProjectileTag;

class Projectile : public GameObject, public IOverlappingObject
{
public:
	explicit Projectile(const Point2f& origin, const Vector2f& initialVelocity, const Vector2f& acceleration, Sprite* sprite, ProjectileTag tag, const Rectf& boundaries, float width, float height, bool isFriendly, bool isFlipped, int damage, int zIndex);
	explicit Projectile(const Transform& transform, const Vector2f& initialVelocity, const Vector2f& acceleration, Sprite* sprite, ProjectileTag tag, const Rectf& boundaries, float width, float height, bool isFriendly, bool isFlipped, int damage, int zIndex);
	Projectile& operator=(const Projectile& rhs) = delete;
	Projectile& operator=(Projectile&& rhs) = delete;
	Projectile(const Projectile& other) = delete;
	Projectile(Projectile&& other) = delete;
	virtual ~Projectile();

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;
	virtual void DrawDebug(int zIndex) const override;
	
	// Inherited via IOverlappingObject
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const std::vector<Point2f>& overlappingShape) override;

	virtual void SetBoundaries(const Rectf& boundaries);
	virtual bool IsFriendly();
	virtual bool IsFlaggedForDeletion() const = 0;
	virtual ProjectileTag GetProjectileTag() const = 0;
	virtual Rectf GetShape() const;
	virtual int GetDamage();

	void AddToImmuneList(int id);
	std::vector<int> GetImmuneList() const;

protected:
	const float m_Width;
	const float m_Height;
	const ProjectileTag m_ProjectileTag;
	const bool m_IsFriendly;
	const int m_Damage;

	Vector2f m_Acceleration;
	Vector2f m_Velocity;
	Sprite* m_pSprite;
	Rectf m_Boundaries;
	bool m_FlaggedForDeletion;
	bool m_IsFlipped;
	std::vector<int> m_ImmuneList;

	virtual Sprite* CreateSprite() = 0;
};