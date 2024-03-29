#pragma once
#include "InteractableObject.h"
class Door final : public InteractableObject
{
public:
	explicit Door(const std::vector<Point2f>& vertices);
	Door& operator=(const Door& rhs) = delete;
	Door& operator=(Door&& rhs) = delete;
	Door(const Door& other) = delete;
	Door(Door&& other) = delete;
	virtual ~Door() = default;

	virtual void Update(float elapsedSec) override;
	virtual void DrawDebug(int zIndex) const override;
	virtual bool HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity);
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	bool IsOverlapping(const Rectf& shape);

	virtual bool TryInteraction(const Rectf& shape, int& zIndex, bool& isOnStairs) override;
	virtual bool IsDoneInteracting(const Character& character) const override;
	virtual bool IsAutoInteracting() const override;
	virtual bool TryAutoInteracting(const Rectf& shape, bool& isOnStairs, int& zIndex) const override;
	virtual bool CheckIfActive(const Point2f& point) const override;
};