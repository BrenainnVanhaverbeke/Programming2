#include "pch.h"
#include "Skeleton.h"
#include "ClackityBoneManMovement.h"

Skeleton::Skeleton(const Transform& transform, LevelManager* pLevelManager, int zIndex, int id)
	: Character
	(
		transform,
		GetSprite(),
		new ClackityBoneManMovement(Vector2f{0, G_GRAVITY}),
		CharacterTypes::skeleton,
		pLevelManager,
		25.0f,
		46.0f,
		zIndex,
		80,
		id
	)
{
}

Skeleton::Skeleton(const Point2f& origin, LevelManager* pLevelManager, int zIndex, int id)
	: Skeleton(Transform{ origin }, pLevelManager, zIndex, id)
{
}

void Skeleton::Update(float elapsedSec)
{
}

void Skeleton::Draw(int zIndex) const
{
}

void Skeleton::CheckOverlap(const Rectf& overlappingShape)
{
}

Sprite* Skeleton::GetSprite() const
{
	return nullptr;
}
