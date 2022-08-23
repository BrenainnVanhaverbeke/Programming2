#pragma once
#include "Character.h"
class Skeleton : public Character
{
public:
	explicit Skeleton(const Transform& transform, LevelManager* pLevelManager, int zIndex, int id);
	explicit Skeleton(const Point2f& origin, LevelManager* pLevelManager, int zIndex, int id);
	Skeleton(const Skeleton& other) = delete;
	Skeleton(Skeleton&& other) = delete;
	Skeleton& operator=(const Skeleton& rhs) = delete;
	Skeleton& operator=(Skeleton&& rhs) = delete;
	virtual ~Skeleton() = default;

	// Inherited via Character
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual Sprite* GetSprite() const override;
};