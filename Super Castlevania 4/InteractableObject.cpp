#include "pch.h"
#include "InteractableObject.h"
#include "utils.h"


InteractableObject::InteractableObject(const std::vector<Point2f>& vertices, int zIndex)
    : TerrainObject(vertices, zIndex)
{
}

bool InteractableObject::CheckDirection(const Vector2f& actorVelocity) const
{
    return false;
}