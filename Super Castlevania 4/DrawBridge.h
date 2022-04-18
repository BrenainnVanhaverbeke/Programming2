#pragma once
#include "TerrainObject.h"

class DrawBridge final : public TerrainObject
{
public:
	explicit DrawBridge(const std::vector<Point2f>& vertices, bool isBackground);
	DrawBridge& operator=(const DrawBridge& rhs) = delete;
	DrawBridge& operator=(DrawBridge&& rhs) = delete;
	DrawBridge(const DrawBridge& other) = delete;
	DrawBridge(DrawBridge&& other) = delete;

	virtual void Update(float elapsedSec) override;
	virtual bool HandleCollisions(Character& character) override;

private:
	bool m_IsClosing;
	float m_RotationAngle;
	float m_RotationSpeed;

	Point2f m_Pivot;
	const std::vector<Point2f> m_BaseVertices;

	void CloseDrawBridge(float elapsedSec);
};