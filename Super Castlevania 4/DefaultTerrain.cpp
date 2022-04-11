#include "pch.h"
#include "DefaultTerrain.h"
#include "Texture.h"
#include "SVGParser.h"
#include <iostream>

DefaultTerrain::DefaultTerrain(const std::vector<Point2f>& vertices)
	: TerrainObject(vertices)
{
}

void DefaultTerrain::Update(float elapsedSec)
{
}

void DefaultTerrain::Draw() const
{
	utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	utils::DrawPolygon(m_Vertices);
}

void DefaultTerrain::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	CheckHorizontalCollisions(m_Vertices, actorShape, actorTransform, actorVelocity, hitInfo);
	CheckVerticalCollisions(m_Vertices, actorShape, actorTransform, actorVelocity, hitInfo);
}

bool DefaultTerrain::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	if (utils::Raycast(m_Vertices, actorShape.GetCenterLeft(), actorShape.GetBottomLeft(0, -1.0f), hitInfo)
		|| utils::Raycast(m_Vertices, actorShape.GetCenterRight(), actorShape.GetBottomRight(0, -1.0f), hitInfo))
		return true;
	return false;
}

void DefaultTerrain::CheckOverlap(const Rectf& overlappingShape)
{
}

void DefaultTerrain::LogPoints(std::vector<Point2f>& points)
{
	size_t nrOfPoints{ points.size() };
	for (size_t i{ 0 }; i < nrOfPoints; ++i)
		std::cout << "{ " << points[i].x << ", " << points[i].y << " }\n";
}

void DefaultTerrain::CheckVerticalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const
{
	if (utils::Raycast(vertices, actorShape.GetCenterLeft(3.0f), actorShape.GetBottomLeft(3.0f, -1.0f), hitInfo)
		|| utils::Raycast(vertices, actorShape.GetCenterRight(-3.0f), actorShape.GetBottomRight(-3.0f, -1.0f), hitInfo))
	{
		actorVelocity.y = 0;
		actorTransform.positionY = hitInfo.intersectPoint.y + 1;
		return;
	}
	if (utils::Raycast(vertices, actorShape.GetCenterLeft(3.0f), actorShape.GetTopLeft(3.0f, 1.0f), hitInfo)
		|| utils::Raycast(vertices, actorShape.GetCenterRight(-3.0f), actorShape.GetTopRight(-3.0f, 1.0f), hitInfo))
	{
		actorVelocity.y = 0;
		actorTransform.positionY = hitInfo.intersectPoint.y - actorShape.height - 1;
		return;
	}
}

void DefaultTerrain::CheckHorizontalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const
{
	std::vector<Point2f> raycastAnchors{ GetRaycastAnchors(actorShape) };
	size_t nrOfAnchors{ raycastAnchors.size() };
	for (size_t i{ 0 }; i < nrOfAnchors; ++i)
	{
		Point2f& anchor{ raycastAnchors[i] };
		Point2f targetLeft{ anchor };
		targetLeft.x -= (actorShape.width / 2) + 1;
		Point2f targetRight{ anchor };
		targetRight.x += (actorShape.width / 2) + 1;
		if (utils::Raycast(vertices, anchor, targetLeft, hitInfo))
		{
			actorVelocity.x = 0;
			actorTransform.positionX = hitInfo.intersectPoint.x + 2;
			return;
		}
		if (utils::Raycast(vertices, anchor, targetRight, hitInfo))
		{
			actorVelocity.x = 0;
			actorTransform.positionX = hitInfo.intersectPoint.x - actorShape.width - 2;
			return;
		}
	}
}

std::vector<Point2f> DefaultTerrain::GetRaycastAnchors(const Rectf& actorShape) const
{
	Point2f topCenter{ actorShape.GetTopCenter(0, -3.0f) };
	Point2f center{ actorShape.GetCenter() };
	Point2f bottomCenter{ actorShape.GetBottomCenter(0, 3.0f) };
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