#include "pch.h"
#include "CrumblingBlock.h"

CrumblingBlock::CrumblingBlock(const std::vector<Point2f>& vertices)
	: DynamicTerrain(vertices)
	, m_StepOnTime{ 0 }
	, m_MaxStepOnTime{ 3.0f }
	, m_IsFalling{ false }
	, m_Acceleration{ -981.0f }
	, m_Velocity{ 0 }
{
}

void CrumblingBlock::Update(float elapsedSec, const Rectf& actorShape)
{
	if (!m_IsFalling && IsOnGround(actorShape, Vector2f{}))
	{
		if (m_MaxStepOnTime < (m_StepOnTime += elapsedSec))
			m_IsFalling = true;;
	}
	else if (m_IsFalling)
	{
		m_Velocity += m_Acceleration * elapsedSec;
		size_t nrOfVertices{ m_Vertices.size() };
		for (size_t i{ 0 }; i < nrOfVertices; ++i)
			m_Vertices.at(i).y += m_Velocity * elapsedSec;
	}
}

void CrumblingBlock::Draw() const
{
	utils::DrawPolygon(m_Vertices);
}

void CrumblingBlock::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const
{
	if (!m_IsFalling)
		DynamicTerrain::HandleCollisions(actorShape, actorTransform, actorVelocity);
}

bool CrumblingBlock::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	if (m_IsFalling)
		return false;
	return utils::Raycast(m_Vertices, actorShape.GetCenter(), actorShape.GetBottomCenter(0, -1.0f), hitInfo);
}