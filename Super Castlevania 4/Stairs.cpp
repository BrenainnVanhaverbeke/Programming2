#include "pch.h"
#include "Stairs.h"
#include "utils.h"

Stairs::Stairs(const std::vector<Point2f>& vertices, int lowPoint, int highPoint, bool autoMountTop, bool autoMountBottom)
	: TerrainObject(vertices)
	, m_LowPoint{ lowPoint }
	, m_HighPoint{ highPoint }
	, m_IsAutoMountingTop{ autoMountTop }
	, m_IsAutoMountingBottom{ autoMountBottom }
{
}

void Stairs::Draw() const
{
	utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	utils::DrawPolygon(m_Vertices);
	utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
	utils::DrawPoint(m_Vertices[m_LowPoint], 5.0f);
	utils::SetColor(Color4f{ 0.0f, 1.0f, 0.0f, 1.0f });
	utils::DrawPoint(m_Vertices[m_HighPoint], 5.0f);
}

bool Stairs::IsOverlapping(const Rectf& shape) const
{
	return utils::IsPointInPolygon(shape.GetBottomCenter(), m_Vertices);
}

bool Stairs::CheckAutoMount(const Rectf& shape) const
{
	const float offset{ 2.0f };
	Point2f anchor{ shape.GetBottomCenter() };
	const Point2f& lowPoint{ m_Vertices[m_LowPoint] };
	const Point2f& highPoint{ m_Vertices[m_HighPoint] };
	bool isInXRange{ lowPoint.x - offset < anchor.x&& anchor.x < lowPoint.x + offset };
	bool isInYRange{ lowPoint.y - offset < anchor.y&& anchor.y < lowPoint.y + offset };
	if (m_IsAutoMountingBottom && isInXRange && isInYRange)
		return true;
	isInXRange = highPoint.x - offset < anchor.x&& anchor.x < highPoint.x + offset;
	isInYRange = highPoint.y - offset < anchor.y&& anchor.y < highPoint.y + offset;
	if (m_IsAutoMountingTop && isInXRange && isInYRange)
		return true;
	return false;
}

bool Stairs::IsEndReached(const Rectf& actorShape) const
{
	const Point2f& anchor{ actorShape.GetBottomCenter() };
	const Point2f& lowPoint{ m_Vertices[m_LowPoint] };
	const Point2f& highPoint{ m_Vertices[m_HighPoint] };
	if (lowPoint.x < highPoint.x)
		return anchor.x < lowPoint.x || highPoint.x < anchor.x;
	return anchor.x < highPoint.x || lowPoint.x < anchor.x;
}

bool Stairs::IsAutoMounting() const
{
	return m_IsAutoMountingBottom;
}

void Stairs::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	if (utils::Raycast(m_Vertices, actorShape.GetCenter(), actorShape.GetBottomCenter(0, -1.0f), hitInfo))
	{
		actorTransform.positionY = hitInfo.intersectPoint.y;
		actorVelocity.y = 0;
	}
}