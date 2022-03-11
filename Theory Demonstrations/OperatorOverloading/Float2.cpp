#include "pch.h"
#include "Float2.h"
#include <ostream>

Float2::Float2(float x, float y)
	: m_X{ x }, m_Y{ y }
{
}

Float2 Float2::operator+=(const Float2& rhs)
{
	m_X += rhs.m_X;
	m_Y += rhs.m_Y;
	return *this;
}

Float2 operator+(Float2 lhs, const Float2& rhs)
{
	lhs += rhs;
	return lhs;
	//return Float2{ lhs.m_X + rhs.m_X, rhs.m_Y + lhs.m_Y };
}

std::string Float2::ToString()
{
	return "(" + std::to_string(m_X) + ", " + std::to_string(m_Y) + ")\n";
}

std::ostream& operator<< (std::ostream& out, const Float2& f)
{
	out << "(" << f.m_X << ", " << f.m_Y << ")\n";
	return out;
}