#pragma once
#include <vector>
#include "TerrainObject.h"
#include "GameObject.h"

class Stairs final : public TerrainObject
{
public:
	explicit Stairs(const std::vector<Point2f>& vercices, int lowPoint, int highPoint, bool autoMountTop, bool autoMountBottom);

	void Draw() const override;

	bool IsOverlapping(const Rectf& shape) const;
	bool CheckAutoMount(const Rectf& shape) const;
	bool IsEndReached(const Rectf& actorShape) const;
	bool IsAutoMounting() const;
	virtual void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const override;

private:
	const int m_LowPoint;
	const int m_HighPoint;
	bool m_IsAutoMountingTop;
	bool m_IsAutoMountingBottom;

	//void CorrectDirection(float lowestX, float highestX, float lowestY, float highestY);
};