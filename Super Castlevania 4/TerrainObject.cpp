#include "pch.h"
#include "TerrainObject.h"
#include "Character.h"
#include <iostream>

TerrainObject::TerrainObject(const std::vector<Point2f>& vertices, int zIndex)
	: TerrainObject(vertices, vertices.at(0), zIndex)
{
}

TerrainObject::TerrainObject(const std::vector<Point2f>& vertices, const Point2f& pivot, int zIndex)
	: GameObject(pivot, zIndex)
	, m_Vertices{ vertices }
	, m_AnchorOffset{ 5.0f }
	, m_RaycastOffset{ 1.0f }
{
}

TerrainObject::~TerrainObject()
{
	m_Vertices.clear();
}

void TerrainObject::Update(float elapsedSec)
{
}

void TerrainObject::Draw(int zIndex) const
{
}

void TerrainObject::DrawDebug(int zIndex) const
{
	if (m_ZIndex == zIndex)
	{
		utils::SetColor(m_ZIndex == -1 ? Color4f{ 1.0f, 0, 0, 1.0f } : Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
		utils::DrawPolygon(m_Vertices);
		utils::SetColor(Color4f{ 1.0f, 0, 0, 1.0f });
		utils::DrawPoint(m_Transform.GetTranslation());
	}
}

void TerrainObject::CheckOverlap(const Rectf& overlappingShape)
{
}

bool TerrainObject::IsOverlapping(const Rectf& overlappingShape)
{
	return false;
}

bool TerrainObject::HandleCollisions(Character& character)
{
	utils::HitInfo hitInfo{};
	bool verticalCollision{ CheckVerticalCollisions(m_Vertices, character, hitInfo) };
	bool horizontalCollision{ CheckHorizontalCollisions(m_Vertices, character, hitInfo) };
	return verticalCollision || horizontalCollision;
}

bool TerrainObject::IsOnGround(const Character& character)
{
	Rectf actorShape{ character.GetShape() };
	utils::HitInfo hitInfo{};
	if (utils::Raycast(m_Vertices, actorShape.GetCenterLeft(), actorShape.GetBottomLeft(0, -1.0f), hitInfo)
		|| utils::Raycast(m_Vertices, actorShape.GetCenterRight(), actorShape.GetBottomRight(0, -1.0f), hitInfo))
		return true;
	return false;
}

bool TerrainObject::CheckVerticalCollisions(const std::vector<Point2f>& vertices, Character& character, utils::HitInfo hitInfo) const
{
	Rectf actorShape{ character.GetShape() };
	Vector2f& actorVelocity{ character.GetVelocity() };
	Transform& actorTransform{ character.GetTransform() };
	bool left{ utils::Raycast(vertices, actorShape.GetCenterLeft(m_AnchorOffset / 2), actorShape.GetBottomLeft(m_AnchorOffset, -1.0f), hitInfo) };
	bool centre{ utils::Raycast(vertices, actorShape.GetCenter(), actorShape.GetBottomCenter(0, -1.0f), hitInfo) };
	bool right{ utils::Raycast(vertices, actorShape.GetCenterRight(-m_AnchorOffset / 2), actorShape.GetBottomRight(-m_AnchorOffset, -1.0f), hitInfo) };
	if (left || centre || right)
	{
		actorVelocity.y = 0;
		actorTransform.positionY = hitInfo.intersectPoint.y;
		return true;
	}
	if (utils::Raycast(vertices, actorShape.GetCenterLeft(m_AnchorOffset / 2), actorShape.GetTopLeft(m_AnchorOffset, 1.0f), hitInfo)
		|| utils::Raycast(vertices, actorShape.GetCenterRight(-m_AnchorOffset / 2), actorShape.GetTopRight(-m_AnchorOffset, 1.0f), hitInfo))
	{
		actorVelocity.y = 0;
		actorTransform.positionY = hitInfo.intersectPoint.y - actorShape.height - m_RaycastOffset;
		return true;
	}
	return false;
}

bool TerrainObject::CheckHorizontalCollisions(const std::vector<Point2f>& vertices, Character& character, utils::HitInfo hitInfo) const
{
	Rectf actorShape{ character.GetShape() };
	Vector2f& actorVelocity{ character.GetVelocity() };
	Transform& actorTransform{ character.GetTransform() };
	std::vector<Point2f> raycastAnchors{ GetRaycastAnchors(actorShape) };
	size_t nrOfAnchors{ raycastAnchors.size() };
	for (size_t i{ 0 }; i < nrOfAnchors; ++i)
	{
		Point2f& anchor{ raycastAnchors[i] };
		Point2f targetLeft{ anchor };
		targetLeft.x -= (actorShape.width / 2) + m_RaycastOffset;
		Point2f targetRight{ anchor };
		targetRight.x += (actorShape.width / 2) + m_RaycastOffset;
		if (utils::Raycast(vertices, anchor, targetLeft, hitInfo))
		{
			actorVelocity.x = 0;
			actorTransform.positionX = hitInfo.intersectPoint.x + m_RaycastOffset;
			return true;
		}
		if (utils::Raycast(vertices, anchor, targetRight, hitInfo))
		{
			actorVelocity.x = 0;
			actorTransform.positionX = hitInfo.intersectPoint.x - actorShape.width - m_RaycastOffset;
			return true;
		}
	}
	return false;
}

std::vector<Point2f> TerrainObject::GetRaycastAnchors(const Rectf& actorShape) const
{
	Point2f topCenter{ actorShape.GetTopCenter(0, -m_AnchorOffset) };
	Point2f center{ actorShape.GetCenter() };
	Point2f bottomCenter{ actorShape.GetBottomCenter(0, m_AnchorOffset) };
	Point2f topCenterMiddle{ utils::GetMiddle(topCenter, center) };
	Point2f bottomCenterMiddle{ utils::GetMiddle(center, bottomCenter) };
	return std::vector<Point2f>
	{
		topCenter,
			center,
			bottomCenter,
			topCenterMiddle,
			bottomCenterMiddle
	};
}