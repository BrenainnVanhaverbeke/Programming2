#include "pch.h"
#include <iostream>
#include "OperatorOverloading.h"
#include "Float2.h"

int main()
{
	Float2 f1{ 20, 20 };
	Float2 f2{ 50, 60 };
	Float2 f3{};
	f3 = f1 + f2;

	std::cout << f1;
	std::cout << f2;
	std::cout << f3;

	f3 += f1;

	std::cout << f3 << "\n";
}