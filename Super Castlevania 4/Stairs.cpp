#include "pch.h"
#include "Stairs.h"
#include "utils.h"
#include <iostream>

Stairs::Stairs(const std::vector<Point2f>& vertices, int lowPoint, int highPoint, bool autoMountTop, bool autoMountBottom, bool isBackground)
	: InteractableObject(vertices, isBackground)
	, m_LowPoint{ m_Vertices.at(lowPoint) }
	, m_HighPoint{ m_Vertices.at(highPoint) }
	, m_IsAutoMountingTop{ autoMountTop }
	, m_IsAutoMountingBottom{ autoMountBottom }
{
}

void Stairs::Draw() const
{
	const Color4f autoMount{ 0, 1.0f, 0, 1.0f };
	const Color4f noAutoMount{ 1.0f, 0, 0, 1.0f };
	const Color4f stairsColour{ 0, 1.0f, 1.0f, 1.0f };
	utils::SetColor(stairsColour);
	utils::DrawPolygon(m_Vertices);
	utils::SetColor(m_IsAutoMountingBottom ? autoMount : noAutoMount);
	utils::DrawPoint(m_LowPoint);
	utils::SetColor(m_IsAutoMountingTop ? autoMount : noAutoMount);
	utils::DrawPoint(m_HighPoint);
}

void Stairs::Update(float elapsedSec)
{
}

void Stairs::CheckOverlap(const Rectf& overlappingShape)
{
}

bool Stairs::IsOverlapping(const Rectf& shape)
{
	return utils::IsPointInPolygon(shape.GetBottomCenter(), m_Vertices);
}

bool Stairs::TryInteraction(const Rectf& shape, bool& isOnBackground, bool& isOnStairs)
{
	if (isOnBackground != m_IsBackground)
		return false;
	const float offset{ 5.0f };
	if (IsAnchorInRange(shape.GetBottomCenter(), m_LowPoint, offset)
		|| IsAnchorInRange(shape.GetBottomCenter(), m_HighPoint, offset))
	{
		std::cout << "Mounting stairs on mount point.\n";
		isOnStairs = true;
		return isOnStairs;
	}
	if (IsOverlapping(shape))
	{
		std::cout << "Mounting stairs on shape overlap.\n";
		isOnStairs = true;
	}
	return isOnStairs;
}

bool Stairs::IsDoneInteracting(const Rectf& actorShape) const
{
	const Point2f& anchor{ actorShape.GetBottomCenter() };
	bool isDoneInteracting{  };
	if (m_LowPoint.x < m_HighPoint.x)
	{
		isDoneInteracting = anchor.x < m_LowPoint.x || m_HighPoint.x < anchor.x;
		return isDoneInteracting;
	}
	isDoneInteracting = anchor.x < m_HighPoint.x || m_LowPoint.x < anchor.x;
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
	const float offset{ 2.0f };
	if (m_IsAutoMountingBottom && IsAnchorInRange(anchor, m_LowPoint, offset)
		|| m_IsAutoMountingTop && IsAnchorInRange(anchor, m_HighPoint, offset))
	{
		isOnStairs = true;
		return isOnStairs;
	}
	isOnStairs = false;
	return isOnStairs;
}

bool Stairs::CheckIfActive(const Point2f& point) const
{
	return utils::IsPointInPolygon(point, m_Vertices);
}

bool Stairs::CheckDirection(const Vector2f& velocity) const
{
	if (m_LowPoint.x < m_HighPoint.x && 0 < velocity.x)
		return true;
	if (m_HighPoint.x < m_LowPoint.x && velocity.x < 0)
		return true;
	return false;
}

bool Stairs::IsAnchorInRange(const Point2f& anchor, const Point2f& mountPoint, float offset) const
{
	bool isInXRange{ mountPoint.x - offset < anchor.x&& anchor.x < mountPoint.x + offset };
	bool isInYRange{ mountPoint.y - offset < anchor.y&& anchor.y < mountPoint.y + offset };
	return isInXRange && isInYRange;
}

bool Stairs::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity)
{
	const float raycastOffset{ 5.0f };
	utils::HitInfo hitInfo{};
	if (utils::Raycast(m_Vertices, actorShape.GetCenter(), actorShape.GetBottomCenter(0, -raycastOffset), hitInfo))
	{
		actorTransform.positionY = hitInfo.intersectPoint.y;
		actorVelocity.y = 0;
		return true;
	}
	return false;
}

bool Stairs::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity)
{
	return false;
}