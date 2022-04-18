#pragma once
#include <vector>

class Projectile;
enum class ProjectileTag;

class ProjectileManager
{
public:
	ProjectileManager();
	ProjectileManager& operator=(const ProjectileManager& rhs) = delete;
	ProjectileManager& operator=(ProjectileManager&& rhs) = delete;
	ProjectileManager(const ProjectileManager& other) = delete;
	ProjectileManager(ProjectileManager&& other) = delete;
	~ProjectileManager();

	void Update(float elapsedSec);
	void Draw() const;
	void AddProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped);
	void SetBoundaries(const Rectf& boundaries);

	void ToggleDrawDebug();

private:
	bool m_IsDrawDebug;
	std::vector<Projectile*> m_pProjectiles;

	void DeleteProjectiles();
	Projectile* CreateProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped) const;
};