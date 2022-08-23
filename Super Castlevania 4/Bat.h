#pragma once
#include "Character.h"
#include "IOverlappingObject.h"

class Bat final : public Character
{
public:
	Bat(const Transform& transform, int zIndex, bool isMovingLeft, int id);
	Bat(const Point2f location, int zIndex, bool isMovingLeft, int id);
	~Bat() = default;

	// Inherited via Character
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

	// Inherited via IOverlappingObject
	virtual void CheckOverlap(const Rectf& overlappingShape) override;

private:
	// Inherited via Character
	virtual Sprite* GetSprite() const override;
};