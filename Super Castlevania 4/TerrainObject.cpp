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
