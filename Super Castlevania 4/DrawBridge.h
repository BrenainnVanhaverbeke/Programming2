#pragma once
#include "DynamicTerrain.h"
class DrawBridge final : public DynamicTerrain
{
public:
	DrawBridge(const std::vector<Point2f>& vertices);

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const Rectf& actorShape);

private:
	bool m_IsClosing;
	float m_RotationAngle;
	float m_RotationSpeed;

	Point2f m_Pivot;
	const std::vector<Point2f> m_BaseVertices;

	void CloseDrawBridge(float elapsedSec);
};