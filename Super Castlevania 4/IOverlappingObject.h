#pragma once
class IOverlappingObject
{
public:
	virtual void CheckOverlap(const Rectf& overlappingShape) = 0;
	virtual bool IsOverlapping(const Rectf& overlappingShape) = 0;
	virtual bool IsOverlapping(const std::vector<Point2f>& overlappingShape) = 0;

	// TODO: Consider possibility of extracting type of colliding object by passing an additional interface?
	// virtual bool IsOverlapping(const MysteryObject& overlappingObject);
};