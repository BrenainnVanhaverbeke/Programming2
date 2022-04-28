#include "pch.h"
#include "InteractableObject.h"
#include "utils.h"


InteractableObject::InteractableObject(const std::vector<Point2f>& vertices, bool isBackground)
    : TerrainObject(vertices, isBackground)
{
}

bool InteractableObject::CheckDirection(const Vector2f& actorVelocity) const
{
    return false;
}