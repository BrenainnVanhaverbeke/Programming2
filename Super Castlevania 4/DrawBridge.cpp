#include "pch.h"
#include "DrawBridge.h"
#include "Matrix2x3.h"

#include <iostream>

DrawBridge::DrawBridge(const std::vector<Point2f>& vertices, bool isBackground)
	: TerrainObject(vertices, isBackground)
	, m_BaseVertices{ m_Vertices }
	, m_RotationAngle{ 0 }
	, m_RotationSpeed{ -5.0f }
	, m_IsClosing{ false }
{
	m_Pivot = m_BaseVertices.at(3);
}

void DrawBridge::Update(float elapsedSec)
{
	if (m_IsClosing)
		CloseDrawBridge(elapsedSec);
}

void DrawBridge::CheckOverlap(const Rectf& overlapShape)
{
	IsOnGround(overlapShape, Vector2f{});
}

bool DrawBridge::IsOverlapping(const Rectf& overlappingShape)
{
	return IsOnGround(overlappingShape, Vector2f{});
}

bool DrawBridge::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity)
{
	if (TerrainObject::HandleCollisions(actorShape, actorTransform, actorVelocity))
	{
		m_IsClosing = true;
		return true;
	}
	return false;
}

void DrawBridge::CloseDrawBridge(float elapsedSec)
{
	Matrix2x3 rotationMatrix, originMatrix, resetMatrix;
	m_RotationAngle += m_RotationSpeed * elapsedSec;
	rotationMatrix.SetAsRotate(m_RotationAngle);
	originMatrix.SetAsTranslate(-m_Pivot.x, -m_Pivot.y);
	resetMatrix.SetAsTranslate(m_Pivot.x, m_Pivot.y);
	Matrix2x3 transformationMatrix{ resetMatrix * rotationMatrix * originMatrix };
	m_Vertices = transformationMatrix.Transform(m_BaseVertices);
}