#pragma once
#include <string>

class Float2 final
{
public:
	Float2(float x = 0.0f, float y = 0.0f);
	Float2 operator+=(const Float2& rhs);
	std::string ToString();

	//friend Float2 operator+(const Float2& lhs, const Float2& rhs);
	friend std::ostream& operator<< (std::ostream& out, const Float2& f);

private:
	float m_X;
	float m_Y;
};

Float2 operator+(Float2 lhs, const Float2& rhs);