#pragma once
#include <vector>
#include "Vector2f.h"

class TerrainObject
{
public:
	explicit TerrainObject(std::vector<Point2f> vertices);
	virtual ~TerrainObject();
	virtual void Draw() const = 0;

	virtual void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const = 0;
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

protected:
	std::vector<Point2f> m_Vertices;
};