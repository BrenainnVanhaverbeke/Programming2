#pragma once
#include "StaticTerrain.h"
class DynamicTerrain : public StaticTerrain
{
public:
    DynamicTerrain(const std::vector<Point2f>& vertices);

    virtual void Update(float elapsedSec, const Rectf& actorShape) = 0;
    virtual void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const override;
};