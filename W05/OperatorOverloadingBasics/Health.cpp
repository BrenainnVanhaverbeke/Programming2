#include "pch.h"
#include "Health.h"

Health::Health(int value)
	: m_Value{ value }
{
}
int Health::GetValue() const
{
	return m_Value;
}

Health& Health::operator+=(int number)
{
	m_Value += number;
	return *this;
}

Health& Health::operator-=(int subtractor)
{
	m_Value -= subtractor;
	return *this;
}

Health operator+(Health lhs, int rhs)
{
	lhs += rhs;
	return lhs;
}

Health operator+(int lhs, Health rhs)
{
	rhs += lhs;
	return rhs;
}

Health operator-(Health lhs, int rhs)
{
	lhs -= rhs;
	return lhs;
}

Health operator-(int lhs, Health rhs)
{
	return Health(lhs - rhs.GetValue());
}
