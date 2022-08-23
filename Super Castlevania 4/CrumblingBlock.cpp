#include "pch.h"
#include "TerrainObject.h"
#include "CrumblingBlock.h"
#include <iostream>

CrumblingBlock::CrumblingBlock(const std::vector<Point2f>& vertices, int zIndex)
	: TerrainObject(vertices, zIndex)
	, m_StepOnTime{ 0 }
	, m_MaxStepOnTime{ 1.5f }
	, m_IsFalling{ false }
	, m_Acceleration{ G_GRAVITY }
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

bool CrumblingBlock::HandleCollisions(Character& character)
{
	if (!m_IsFalling && TerrainObject::HandleCollisions(character))
	{
		m_IsOverlapped = true;
		return true;
	}
	m_IsOverlapped = false;
	return false;
}

bool CrumblingBlock::IsOnGround(const Character& character)
{
	utils::HitInfo hitInfo{};
	if (m_IsFalling)
		return false;
	return TerrainObject::IsOnGround(character);
}

void CrumblingBlock::CheckOverlap(const Rectf& overlappingShape)
{
}

bool CrumblingBlock::IsOverlapping(const Rectf& overlappingShape) 
{
	return false;
}