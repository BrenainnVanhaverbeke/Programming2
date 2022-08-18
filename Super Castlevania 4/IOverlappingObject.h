#pragma once
class IOverlappingObject
{
public:
	virtual void CheckOverlap(const Rectf& overlappingShape) = 0;
	virtual bool IsOverlapping(const Rectf& overlappingShape) = 0;
};