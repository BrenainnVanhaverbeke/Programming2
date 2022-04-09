#pragma once
#include <vector>
#include "TerrainObject.h"
#include "GameObject.h"

class Stairs final : public TerrainObject
{
public:
	explicit Stairs(const std::vector<Point2f>& vertices);

	void Draw() const override;

	bool IsOverlapping(const Rectf& shape) const;
	bool IsEndReached(const Rectf& actorShape) const;
	bool IsAutoMounting() const;
	virtual void HandleCollisions(const Rectf& actorShape, Transformation& actorTransform, Vector2f& actorVelocity) const override;
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const override;

private:
	Point2f m_Lowest;
	Point2f m_Highest;
	bool m_IsAutoMounting;

	void SetPoints();
};