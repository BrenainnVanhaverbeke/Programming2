#include "pch.h"
#include "Terrain.h"
#include "Texture.h"
#include "SVGParser.h"
#include <iostream>

Terrain::Terrain(const std::string& path)
{
	if (!SVGParser::GetVerticesFromSvgFile(path, m_pVertices))
		std::cout << "Level failed to load from svg" << std::endl;
}

Terrain::Terrain(const std::vector<std::vector<Point2f>>& vertices)
	: m_pVertices{ vertices }
{
}

Terrain::~Terrain()
{
	size_t nrOfVertices{ m_pVertices.size() };
	size_t nrOfPoints{};
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		std::vector<Point2f>& vertices{ m_pVertices[i] };
		vertices.clear();
	}
	m_pVertices.clear();
}

void Terrain::Draw() const
{
	utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	for (size_t i = 0; i < m_pVertices.size(); i++)
		utils::DrawPolygon(m_pVertices[i]);
}

void Terrain::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const
{
	size_t nrOfVertices{ m_pVertices.size() };
	utils::HitInfo hitInfo{};
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		CheckHorizontalCollisions(m_pVertices[i], actorShape, actorTransform, actorVelocity, hitInfo);
		CheckVerticalCollisions(m_pVertices[i], actorShape, actorTransform, actorVelocity, hitInfo);
	}
}

bool Terrain::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	size_t verticesSize{ m_pVertices.size() };
	for (size_t i = 0; i < verticesSize; i++)
	{
		if (utils::Raycast(m_pVertices[i], actorShape.GetCenterLeft(), actorShape.GetBottomLeft(0, -1.0f), hitInfo)
			|| utils::Raycast(m_pVertices[i], actorShape.GetCenterRight(), actorShape.GetBottomRight(0, -1.0f), hitInfo))
			return true;
	}
	return false;
}

void Terrain::LogPoints(std::vector<Point2f>& points)
{
	size_t nrOfPoints{ points.size() };
	for (size_t i = 0; i < nrOfPoints; i++)
		std::cout << "{ " << points[i].x << ", " << points[i].y << " }\n";
}

void Terrain::CheckVerticalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const
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

void Terrain::CheckHorizontalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const
{
	std::vector<Point2f> raycastAnchors{ GetRaycastAnchors(actorShape) };
	size_t nrOfAnchors{ raycastAnchors.size() };
	for (size_t i = 0; i < nrOfAnchors; i++)
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

std::vector<Point2f> Terrain::GetRaycastAnchors(const Rectf& actorShape) const
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
