#include "pch.h"
#include "InteractableObject.h"
#include "utils.h"


InteractableObject::InteractableObject(const std::vector<Point2f>& vertices, bool isBackground)
    : TerrainObject(vertices, isBackground)
{
}