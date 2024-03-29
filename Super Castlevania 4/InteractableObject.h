#pragma once
#include "TerrainObject.h"

class InteractableObject : public TerrainObject
{
public:
	explicit InteractableObject(const std::vector<Point2f>& vertices, int zIndex);
	InteractableObject& operator=(const InteractableObject& rhs) = delete;
	InteractableObject& operator=(InteractableObject&& rhs) = delete;
	InteractableObject(const InteractableObject& other) = delete;
	InteractableObject(InteractableObject&& other) = delete;
	virtual ~InteractableObject() = default;

	virtual bool TryInteraction(const Rectf& shape, int& zIndex, bool& isOnStairs) = 0;
	virtual bool IsDoneInteracting(const Character& character) const = 0;
	virtual bool IsAutoInteracting() const = 0;
	virtual bool TryAutoInteracting(const Rectf& shape, bool& isOnStairs, int& zIndex) const = 0;
	virtual bool CheckIfActive(const Point2f& point) const = 0;
	virtual bool CheckDirection(bool isFlipped) const;
};