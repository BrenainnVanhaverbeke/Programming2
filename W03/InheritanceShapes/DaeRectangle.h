#pragma once
#include "Vector2f.h"
#include "DaeShape.h"

class DaeRectangle : public DaeShape
{
public:
	DaeRectangle( const Point2f& center, float width, float height, const Color4f& colour );
	void Draw() const;
};

 
