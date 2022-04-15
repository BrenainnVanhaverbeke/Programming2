#pragma once
#include <vector>
#include "InteractableObject.h"

class Stairs final : public InteractableObject
{
public:
	explicit Stairs(const std::vector<Point2f>& vercices, int lowPoint, int highPoint, bool autoMountTop, bool autoMountBottom, bool isBackground);

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;

	virtual bool IsOverlapping(const Rectf& shape) override;
	virtual bool HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) override;
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) override;
	
	virtual bool TryInteraction(const Rectf& shape, bool& isOnBackground, bool& isOnStairs) override;
	virtual bool IsDoneInteracting(const Rectf& actorShape) const override;
	virtual bool IsAutoInteracting() const override;
	virtual bool TryAutoInteracting(const Rectf& shape, bool& isOnStairs, bool& isOnBackground) const override;
	virtual bool CheckIfActive(const Point2f& point) const override;

private:
	const Point2f& m_LowPoint;
	const Point2f& m_HighPoint;
	bool m_IsAutoMountingTop;
	bool m_IsAutoMountingBottom;

	bool IsAnchorInRange(const Point2f& anchor, const Point2f& mountPoint, float offset) const;
};