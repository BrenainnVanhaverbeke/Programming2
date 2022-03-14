#include "pch.h"		
#include "DaeEllipse.h"
#include "utils.h"

DaeEllipse::DaeEllipse(const Point2f& center, float width, float height, const Color4f& colour, bool isFilled)
	:DaeShape(center, colour, width, height)
	, m_IsFilled{ isFilled }
{
}

void DaeEllipse::Draw() const
{
	utils::SetColor(m_Colour);
	if (m_IsFilled)
	{
		utils::FillEllipse(m_Center, m_Width / 2, m_Height / 2);
	}
	else
	{
		utils::DrawEllipse(m_Center, m_Width / 2, m_Height / 2);
	}
}