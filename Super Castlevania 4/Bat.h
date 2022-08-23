#pragma once
#include "Character.h"
#include "IOverlappingObject.h"

class Bat final : public Character
{
public:
	explicit Bat(const Transform& transform, int zIndex, bool isMovingLeft, int id);
	explicit Bat(const Point2f location, int zIndex, bool isMovingLeft, int id);
	Bat(const Bat& other) = delete;
	Bat(Bat&& other) = delete;
	Bat& operator=(const Bat& rhs) = delete;
	Bat& operator=(Bat&& rhs) = delete;
	virtual ~Bat() = default;

	// Inherited via Character
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

	// Inherited via IOverlappingObject
	virtual void CheckOverlap(const Rectf& overlappingShape) override;

private:
	// Inherited via Character
	virtual Sprite* GetSprite() const override;
};