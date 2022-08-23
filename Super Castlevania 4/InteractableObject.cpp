#include "pch.h"
#include "InteractableObject.h"
#include "utils.h"


InteractableObject::InteractableObject(const std::vector<Point2f>& vertices, int zIndex)
    : TerrainObject(vertices, zIndex)
{
}

bool InteractableObject::CheckDirection(bool isFlipped) const
{
    return false;
}