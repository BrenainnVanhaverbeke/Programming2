#pragma once
#include "TerrainObject.h"

class InteractableObject : public TerrainObject
{
public:
	explicit InteractableObject(const std::vector<Point2f>& vertices, bool isBackground);

	virtual bool TryInteraction(const Rectf& shape, bool& isOnBackground, bool& isOnStairs) = 0;
	virtual bool IsDoneInteracting(const Rectf& shape) const = 0;
	virtual bool IsAutoInteracting() const = 0;
	virtual bool TryAutoInteracting(const Rectf& shape, bool& isOnStairs, bool& isOnBackground) const = 0;
	virtual bool CheckIfActive(const Point2f& point) const = 0;
};