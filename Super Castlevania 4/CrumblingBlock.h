#pragma once
#include "TerrainObject.h"

class CrumblingBlock final : public TerrainObject
{
public:
	CrumblingBlock(const std::vector<Point2f>& vertices);

private:
	std::vector<Point2f> GenerateVertices(const Point2f& origin);
};

