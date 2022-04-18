#pragma once
#include "TerrainObject.h"

class CrumblingBlock final : public TerrainObject
{
public:
	explicit CrumblingBlock(const std::vector<Point2f>& vertices, bool isBackground);
	virtual ~CrumblingBlock();
	CrumblingBlock& operator=(const CrumblingBlock& rhs) = delete;
	CrumblingBlock& operator=(CrumblingBlock&& rhs) = delete;
	CrumblingBlock(const CrumblingBlock& other) = delete;
	CrumblingBlock(CrumblingBlock&& other) = delete;


	virtual void Update(float elapsedSec) override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;

	virtual bool HandleCollisions(Character& character) override;
	virtual bool IsOnGround(const Character& character) override;

private:
	float m_StepOnTime;
	float m_MaxStepOnTime;
	bool m_IsFalling;
	const float m_Acceleration;
	float m_Velocity;
};