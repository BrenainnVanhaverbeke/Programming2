#pragma once
#include <vector>
#include "GameObject.h"

class Projectile;
class Character;
enum class ProjectileTag;

class ProjectileManager final : public GameObject
{
public:
	ProjectileManager();
	ProjectileManager(const ProjectileManager& other) = delete;
	ProjectileManager(ProjectileManager&& other) = delete;
	ProjectileManager& operator=(const ProjectileManager& rhs) = delete;
	ProjectileManager& operator=(ProjectileManager&& rhs) = delete;
	virtual ~ProjectileManager();

	void AddProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped, int zIndex);
	void SetBoundaries(const Rectf& boundaries);

	void Update(float elapsedSec, const Point2f& cameraBottomLeft);

	// Inherited via GameObject
	virtual void Draw(int zIndex) const override;
	virtual void DrawDebug(int zIndex) const override;

	void CheckOverlap(std::vector<Character*>& enemies, Character* player);
	void ResolveProjectileHit(Character* character, Projectile* projectile);

private:
	Rectf m_Boundaries;
	bool m_IsDrawDebug;
	std::vector<Projectile*> m_pProjectiles;

	void DeleteProjectiles();
	void DeleteProjectile(Projectile* projectile);
	Projectile* CreateProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped, int zIndex) const;
	virtual void Update(float elapsedSec) override;
};