#include "pch.h"
#include "DaeShape.h"

DaeShape::DaeShape(const Point2f& center, const Color4f& colour, float width, float height)
	:m_Center{ center }, m_Colour{ colour }, m_Width{ width }, m_Height{ height }
{
}

void DaeShape::Draw() const
{
}

void DaeShape::Translate(const Vector2f& translateVector)
{
	m_Center += translateVector;
}
