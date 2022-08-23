#pragma once
#include <vector>
#include "InteractableObject.h"

class Stairs final : public InteractableObject
{
public:
	explicit Stairs(const std::vector<Point2f>& vercices, int lowPoint, int highPoint, bool autoMountTop, bool autoMountBottom, int zIndex);
	Stairs& operator=(const Stairs& rhs) = delete;
	Stairs& operator=(Stairs&& rhs) = delete;
	Stairs(const Stairs& other) = delete;
	Stairs(Stairs&& other) = delete;
	virtual ~Stairs() = default;

	virtual void DrawDebug(int zIndex) const override;
	virtual void Update(float elapsedSec) override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;

	virtual bool IsOverlapping(const Rectf& shape) override;
	virtual bool HandleCollisions(Character& character) override;
	virtual bool IsOnGround(const Character& character) override;
	
	virtual bool TryInteraction(const Rectf& shape, int& zIndex, bool& isOnStairs) override;
	virtual bool IsDoneInteracting(const Character& character) const override;
	virtual bool IsAutoInteracting() const override;
	virtual bool TryAutoInteracting(const Rectf& shape, bool& isOnStairs, int& zIndex) const override;
	virtual bool CheckIfActive(const Point2f& point) const override;
	virtual bool CheckDirection(bool isFlipped) const override;

private:
	const Point2f& m_LowPoint;
	const Point2f& m_HighPoint;
	bool m_IsAutoMountingTop;
	bool m_IsAutoMountingBottom;

	bool IsAnchorInRange(const Point2f& anchor, const Point2f& mountPoint, float offset) const;
	bool IsCharacterInBounds(const Point2f& anchor) const;
};