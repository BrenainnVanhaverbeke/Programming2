#pragma once
#include "InteractableObject.h"
class Door final : public InteractableObject
{
public:
	Door(const std::vector<Point2f>& vertices);

	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	virtual bool HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity);
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	bool IsOverlapping(const Rectf& shape);

	virtual bool TryInteraction(const Rectf& shape, bool& isOnBackground, bool& isOnStairs) override;
	virtual bool IsDoneInteracting(const Rectf& shape) const override;
	virtual bool IsAutoInteracting() const override;
	virtual bool TryAutoInteracting(const Rectf& shape, bool& isOnStairs, bool& isOnBackground) const override;
	virtual bool CheckIfActive(const Point2f& point) const override;
};