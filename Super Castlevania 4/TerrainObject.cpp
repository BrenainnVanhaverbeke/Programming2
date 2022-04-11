#include "pch.h"
#include "TerrainObject.h"
#include "utils.h"

TerrainObject::TerrainObject(const std::vector<Point2f>& vertices)
	: GameObject(vertices.at(0))
	, m_Vertices{ vertices }
{	
}

TerrainObject::~TerrainObject()
{
	m_Vertices.clear();
}

void TerrainObject::Draw() const
{
	utils::DrawPolygon(m_Vertices);
}

void TerrainObject::Update(float elapsedSec)
{
}

bool TerrainObject::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	return false;
}