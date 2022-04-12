#include "pch.h"
#include "Door.h"
#include "utils.h"



Door::Door(const std::vector<Point2f>& vertices)
	:InteractableObject(vertices, false)
{
}

void Door::Update(float elapsedSec)
{
}

void Door::Draw() const
{
	utils::SetColor(Color4f{ 0, 1.0f, 0, 1.0f });
	utils::DrawPolygon(m_Vertices);
}

void Door::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const
{
}

bool Door::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	return false;
}

void Door::CheckOverlap(const Rectf& overlappingShape)
{
}

bool Door::IsOverlapping(const Rectf& shape) const
{
	return utils::IsPointInPolygon(shape.GetCenter(), m_Vertices);
}

bool Door::TryInteraction(const Rectf& shape, bool& isOnBackground, bool& isOnStairs) const
{
	if (IsOverlapping(shape))
	{
		isOnBackground = !isOnBackground;
		return true;
	}
	return false;
}

bool Door::IsDoneInteracting(const Rectf& shape) const
{
	return true;
}

bool Door::IsAutoInteracting() const
{
	return false;
}

bool Door::TryAutoInteracting(const Rectf& shape, bool& isOnStairs, bool& isOnBackground) const
{
	return false;
}
