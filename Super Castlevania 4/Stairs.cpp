#include "pch.h"
#include "Stairs.h"
#include "utils.h"

Stairs::Stairs(const std::vector<Point2f>& vertices)
	: TerrainObject(vertices)
	, m_IsAutoMounting{ vertices.size() == 5 }
{
	if (m_IsAutoMounting) m_Vertices.pop_back();
	SetPoints();
}

void Stairs::Draw() const
{
	utils::DrawPolygon(m_Vertices);
	utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
	utils::DrawPoint(m_Lowest, 3.0f);
	utils::DrawPoint(m_Highest, 3.0f);
}

bool Stairs::IsOverlapping(const Rectf& shape) const
{
	return utils::IsPointInPolygon(shape.GetBottomCenter(), m_Vertices);
}

bool Stairs::IsEndReached(const Rectf& actorShape) const
{
	const Point2f& anchor{ actorShape.GetBottomCenter() };

	return anchor.x < m_Lowest.x || m_Highest.x < anchor.x;
}

bool Stairs::IsAutoMounting() const
{
	return m_IsAutoMounting;
}

void Stairs::HandleCollisions(const Rectf& actorShape, Transformation& actorTransform, Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	if (utils::Raycast(m_Vertices, actorShape.GetCenter(), actorShape.GetBottomCenter(0, -1.0f), hitInfo))
	{
		actorTransform.positionY = hitInfo.intersectPoint.y;
		actorVelocity.y = 0;
	}
}

bool Stairs::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	return false;
}

void Stairs::SetPoints()
{
	size_t nrOfVertices{ m_Vertices.size() };
	bool isOutOfBounds{ false };
	float lowestX{ 9000.1f };
	float highestX{ -9000.1f };
	float lowestY{ 9000.1f };
	float highestY{ -9000.1f };
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		const Point2f& point{ m_Vertices[i] };
		if (m_Vertices[i].x < lowestX) lowestX = m_Vertices[i].x;
		if (highestX < m_Vertices[i].x) highestX = m_Vertices[i].x;
		if (m_Vertices[i].y < lowestY) lowestY = m_Vertices[i].y;
		if (highestY < m_Vertices[i].y) highestY = m_Vertices[i].y;
	}
	m_Lowest = Point2f{ lowestX, lowestY };
	m_Highest = Point2f{ highestX, highestY };
}
