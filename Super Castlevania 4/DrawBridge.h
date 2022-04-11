#pragma once
#include "DefaultTerrain.h"

class DrawBridge final : public DefaultTerrain
{
public:
	DrawBridge(const std::vector<Point2f>& vertices);

	virtual void Update(float elapsedSec) override;
	virtual void CheckOverlap(const Rectf& overlapShape) override;

private:
	bool m_IsClosing;
	float m_RotationAngle;
	float m_RotationSpeed;

	Point2f m_Pivot;
	const std::vector<Point2f> m_BaseVertices;

	void CloseDrawBridge(float elapsedSec);
};