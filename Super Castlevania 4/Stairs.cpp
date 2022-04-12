#include "pch.h"
#include "Stairs.h"
#include "utils.h"

Stairs::Stairs(const std::vector<Point2f>& vertices, int lowPoint, int highPoint, bool autoMountTop, bool autoMountBottom, bool isBackground)
	: InteractableObject(vertices, isBackground)
	, m_LowPoint{ lowPoint }
	, m_HighPoint{ highPoint }
	, m_IsAutoMountingTop{ autoMountTop }
	, m_IsAutoMountingBottom{ autoMountBottom }
{
}

void Stairs::Draw() const
{
	const Color4f autoMount{ 0, 1.0f, 0, 1.0f };
	const Color4f noAutoMount{ 1.0f, 0, 0, 1.0f };
	TerrainObject::Draw();
	utils::SetColor(m_IsAutoMountingBottom ? autoMount : noAutoMount);
	utils::DrawPoint(m_Vertices[m_LowPoint], 5.0f);
	utils::SetColor(m_IsAutoMountingTop ? autoMount : noAutoMount);
	utils::DrawPoint(m_Vertices[m_HighPoint], 5.0f);
}

void Stairs::Update(float elapsedSec)
{
}

void Stairs::CheckOverlap(const Rectf& overlappingShape)
{
}

bool Stairs::IsOverlapping(const Rectf& shape) const
{
	return utils::IsPointInPolygon(shape.GetBottomCenter(), m_Vertices);
}

bool Stairs::TryInteraction(const Rectf& shape, bool& isOnBackground, bool& isOnStairs) const
{
	if (isOnBackground != m_IsBackground)
		return false;
	isOnStairs = IsOverlapping(shape);
	return isOnStairs;
}

bool Stairs::IsDoneInteracting(const Rectf& actorShape) const
{
	const Point2f& anchor{ actorShape.GetBottomCenter() };
	const Point2f& lowPoint{ m_Vertices[m_LowPoint] };
	const Point2f& highPoint{ m_Vertices[m_HighPoint] };
	bool isDoneInteracting{  };
	if (lowPoint.x < highPoint.x)
	{
		isDoneInteracting = anchor.x < lowPoint.x || highPoint.x < anchor.x;
		return isDoneInteracting;
	}
	isDoneInteracting = anchor.x < highPoint.x || lowPoint.x < anchor.x;
	return isDoneInteracting;
}

bool Stairs::IsAutoInteracting() const
{
	return m_IsAutoMountingBottom || m_IsAutoMountingTop;
}

bool Stairs::TryAutoInteracting(const Rectf& shape, bool& isOnStairs, bool& isOnBackground) const
{
	if (isOnStairs) return isOnStairs;
	if (isOnBackground != m_IsBackground) return false;
	const Point2f& anchor{ shape.GetBottomCenter() };
	const Point2f& lowPoint{ m_Vertices[m_LowPoint] };
	const Point2f& highPoint{ m_Vertices[m_HighPoint] };
	if (m_IsAutoMountingBottom && IsAnchorInRange(anchor, lowPoint)
		|| m_IsAutoMountingTop && IsAnchorInRange(anchor, highPoint))
	{
		isOnStairs = true;
		return isOnStairs;
	}
	isOnStairs = false;
	return isOnStairs;
}

bool Stairs::IsAnchorInRange(const Point2f& anchor, const Point2f& mountPoint) const
{
	const float offset{ 2.0f };
	bool isInXRange{ mountPoint.x - offset < anchor.x&& anchor.x < mountPoint.x + offset };
	bool isInYRange{ mountPoint.y - offset < anchor.y&& anchor.y < mountPoint.y + offset };
	return isInXRange && isInYRange;
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