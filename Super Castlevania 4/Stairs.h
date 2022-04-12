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

	virtual bool IsOverlapping(const Rectf& shape) const override;
	virtual void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const override;
	
	virtual bool TryInteraction(const Rectf& shape, bool& isOnBackground, bool& isOnStairs) const override;
	virtual bool IsDoneInteracting(const Rectf& actorShape) const override;
	virtual bool IsAutoInteracting() const override;
	virtual bool TryAutoInteracting(const Rectf& shape, bool& isOnStairs, bool& isOnBackground) const override;

private:
	const int m_LowPoint;
	const int m_HighPoint;
	bool m_IsAutoMountingTop;
	bool m_IsAutoMountingBottom;

	bool IsAnchorInRange(const Point2f& anchor, const Point2f& mountPoint) const;
};