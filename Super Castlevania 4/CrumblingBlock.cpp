#include "pch.h"
#include "CrumblingBlock.h"



CrumblingBlock::CrumblingBlock(const std::vector<Point2f>& vertices)
	:TerrainObject(vertices)
{
}

std::vector<Point2f> CrumblingBlock::GenerateVertices(const Point2f& origin)
{
	return std::vector<Point2f>();
}
