#include "pch.h"
#include "CrumblingBlock.h"

CrumblingBlock::CrumblingBlock(const std::vector<Point2f>& vertices, bool isBackground)
	: DefaultTerrain(vertices, isBackground)
	, m_StepOnTime{ 0 }
	, m_MaxStepOnTime{ 3.0f }
	, m_IsFalling{ false }
	, m_Acceleration{ -981.0f }
	, m_Velocity{ 0 }
{
}

void CrumblingBlock::Update(float elapsedSec)
{
	if (m_IsOverlapped)
	{
		m_StepOnTime += elapsedSec;
		m_IsFalling = m_MaxStepOnTime < m_StepOnTime;
	}
	if (m_IsFalling)
	{
		m_Velocity += m_Acceleration * elapsedSec;
		size_t nrOfVertices{ m_Vertices.size() };
		for (size_t i{ 0 }; i < nrOfVertices; ++i)
			m_Vertices.at(i).y += m_Velocity * elapsedSec;
	}
}

void CrumblingBlock::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const
{
	if (!m_IsFalling)
		DefaultTerrain::HandleCollisions(actorShape, actorTransform, actorVelocity);
}

bool CrumblingBlock::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	if (m_IsFalling)
		return false;
	return DefaultTerrain::IsOnGround(actorShape, actorVelocity);
}

void CrumblingBlock::CheckOverlap(const Rectf& overlappingShape)
{
	m_IsOverlapped = IsOnGround(overlappingShape, Vector2f{});
}

bool CrumblingBlock::IsOverlapping(const Rectf& overlappingShape) const
{
	return false;
}
