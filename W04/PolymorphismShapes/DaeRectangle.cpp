#include "pch.h"		
#include "DaeRectangle.h"
#include "utils.h"

DaeRectangle::DaeRectangle(const Point2f& center, float width, float height, const Color4f& colour)
	: DaeShape(center, colour, width, height)
{
}

void DaeRectangle::Draw() const
{
	utils::SetColor(m_Colour);
	utils::FillRect(Point2f{ m_Center.x - m_Width / 2,m_Center.y - m_Height / 2 }, m_Width, m_Height);
}