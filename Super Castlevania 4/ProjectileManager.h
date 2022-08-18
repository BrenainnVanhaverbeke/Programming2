#pragma once
#include <vector>
#include "GameObject.h"

class Projectile;
enum class ProjectileTag;

class ProjectileManager final : public GameObject
{
public:
	ProjectileManager();
	ProjectileManager& operator=(const ProjectileManager& rhs) = delete;
	ProjectileManager& operator=(ProjectileManager&& rhs) = delete;
	ProjectileManager(const ProjectileManager& other) = delete;
	ProjectileManager(ProjectileManager&& other) = delete;
	~ProjectileManager();

	void AddProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped);
	void SetBoundaries(const Rectf& boundaries);

	void ToggleDrawDebug();

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

private:
	bool m_IsDrawDebug;
	std::vector<Projectile*> m_pProjectiles;

	void DeleteProjectiles();
	Projectile* CreateProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped) const;
};