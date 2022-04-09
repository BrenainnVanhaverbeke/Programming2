#include "pch.h"
#include "GeneralUtils.h"

Point2f GeneralUtils::GetMiddle(const Point2f& point1, const Point2f& point2)
{
	float middleX{ (point1.x + point2.x) / 2 };
	float middleY{ (point1.y + point2.y) / 2 };
	return Point2f{ middleX, middleY };
}

int GeneralUtils::GetRandomNumber(int lowestValue, int highestValue, bool isInclusive)
{
	int amountOfValues{ highestValue - lowestValue };
	if (isInclusive)
		amountOfValues++;
	return (rand() % amountOfValues) + lowestValue;
}