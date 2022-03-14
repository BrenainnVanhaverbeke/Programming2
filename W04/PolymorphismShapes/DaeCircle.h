#pragma once
#include "Vector2f.h"
#include "DaeEllipse.h"

class DaeCircle : public DaeEllipse
{
public:
	DaeCircle(const Point2f& center, float diameter, const Color4f& colour, bool isFilled);
	virtual void Draw() const override;

private:
	float m_Diameter;
};