#pragma once
#include <string>
#include "Fraction.h"

template<typename T>
T Max(T a, T b);

template<typename T>
T Max(T a, T b)
{
	return a < b ? b : a;
}