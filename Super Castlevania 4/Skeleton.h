#pragma once
#include "Character.h"
class Skeleton : public Character
{
public:
	// Inherited via Character
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual Sprite* GetSprite() const override;
};