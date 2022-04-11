#pragma once
#include "DefaultTerrain.h"

class CrumblingBlock final : public DefaultTerrain
{
public:
	CrumblingBlock(const std::vector<Point2f>& vertices);

	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;

	virtual void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const override;
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const override;

private:
	float m_StepOnTime;
	float m_MaxStepOnTime;
	bool m_IsFalling;
	const float m_Acceleration;
	float m_Velocity;
};