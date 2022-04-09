#include "pch.h"
#include "TerrainObject.h"

TerrainObject::TerrainObject(std::vector<Point2f> vertices)
	: m_Vertices{ vertices }
{	
}

TerrainObject::~TerrainObject()
{
	m_Vertices.clear();
}

bool TerrainObject::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	return false;
}
