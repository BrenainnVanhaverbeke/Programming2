#pragma once
#include "Vector2f.h"
#include "utils.h"
#include "TerrainObject.h"
#include <vector>


class Texture;

class DefaultTerrain : public TerrainObject
{
public:
	explicit DefaultTerrain(const std::vector<Point2f>& vertices);

	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	virtual void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const override;
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;

private:
	void CheckVerticalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const;
	void CheckHorizontalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const;
	std::vector<Point2f> GetRaycastAnchors(const Rectf& actorShape) const;

	void LogPoints(std::vector<Point2f>& points);
};