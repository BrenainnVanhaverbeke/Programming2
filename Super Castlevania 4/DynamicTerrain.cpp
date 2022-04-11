#include "pch.h"
#include "DynamicTerrain.h"

DynamicTerrain::DynamicTerrain(const std::vector<Point2f>& vertices)
	: StaticTerrain(vertices)
{
}

void DynamicTerrain::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const
{
	StaticTerrain::HandleCollisions(actorShape, actorTransform, actorVelocity);
}
