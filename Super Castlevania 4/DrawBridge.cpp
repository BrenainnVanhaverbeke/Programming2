#include "pch.h"
#include "DrawBridge.h"
#include "Matrix2x3.h"

#include <iostream>

DrawBridge::DrawBridge(const std::vector<Point2f>& vertices)
	: DynamicTerrain(vertices)
	, m_BaseVertices{ m_Vertices }
	, m_RotationAngle{ 0 }
	, m_RotationSpeed{ -5.0f }
	, m_IsClosing{ false }
{
	m_Pivot = m_BaseVertices.at(3);
}

void DrawBridge::Draw() const
{
	utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
	utils::DrawPolygon(m_BaseVertices);
	utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	utils::DrawPolygon(m_Vertices);
}

void DrawBridge::Update(float elapsedSec, const Rectf& actorShape)
{
	if (!m_IsClosing && IsOnGround(actorShape, Vector2f{}))
		m_IsClosing = true;
	if (m_IsClosing)
		CloseDrawBridge(elapsedSec);
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