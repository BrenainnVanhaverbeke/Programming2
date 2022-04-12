#include "pch.h"
#include "TerrainObject.h"
#include "utils.h"

TerrainObject::TerrainObject(const std::vector<Point2f>& vertices, bool isBackground)
	: GameObject(vertices.at(0))
	, m_Vertices{ vertices }
	, m_IsBackground{ isBackground }
{	
}

TerrainObject::~TerrainObject()
{
	m_Vertices.clear();
}

void TerrainObject::Draw() const
{
	utils::SetColor(m_IsBackground ? Color4f{ 1.0f, 0, 0, 1.0f } : Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	utils::DrawPolygon(m_Vertices);
}

bool TerrainObject::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	return false;
}

bool TerrainObject::IsBackground() const
{
	return m_IsBackground;
}