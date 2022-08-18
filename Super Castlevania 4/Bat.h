#pragma once
#include "Character.h"
#include "IOverlappingObject.h"

class Bat final : public Character, public IOverlappingObject
{
public:
	Bat(Transform transform, Sprite* sprite, int zIndex);
	~Bat() = default;

	// Inherited via Character
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

	// Inherited via IOverlappingObject
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;
};