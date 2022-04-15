#pragma once
#include "TerrainObject.h"

class DrawBridge final : public TerrainObject
{
public:
	DrawBridge(const std::vector<Point2f>& vertices, bool isBackground);

	virtual void Update(float elapsedSec) override;
	virtual void CheckOverlap(const Rectf& overlapShape) override;
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;

	virtual bool HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) override;

private:
	bool m_IsClosing;
	float m_RotationAngle;
	float m_RotationSpeed;

	Point2f m_Pivot;
	const std::vector<Point2f> m_BaseVertices;

	void CloseDrawBridge(float elapsedSec);
};