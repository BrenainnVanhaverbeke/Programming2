#pragma once
#include "DynamicTerrain.h"

class CrumblingBlock final : public DynamicTerrain
{
public:
	CrumblingBlock(const std::vector<Point2f>& vertices);
	void Update(float elapsedSec, const Rectf& actorShape);
	virtual void Draw() const override;
	virtual void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const override;
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const override;

private:
	float m_StepOnTime;
	float m_MaxStepOnTime;
	bool m_IsFalling;
	const float m_Acceleration;
	float m_Velocity;
};