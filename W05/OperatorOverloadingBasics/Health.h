#pragma once

class Health final
{
public:
	Health(int value);
	int GetValue() const;
	Health& operator +=(int number);
	Health& operator -=(int subtractor);

private:
	int m_Value;
};

Health operator +(Health lhs, int rhs);
Health operator +(int lhs, Health rhs);
Health operator -(Health lhs, int rhs);
Health operator -(int lhs, Health rhs);