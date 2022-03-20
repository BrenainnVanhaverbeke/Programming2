#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "SVGParser.h"
#include <iostream>

Level::Level()
	: m_pBackgroundTexture{ new Texture("Resources/Images/background.png") }
	, m_pForegroundTexture{ new Texture("Resources/Images/fence.png") }
	, m_Boundaries{ 0.0f, 0.0f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight() }
{
	std::vector<std::vector<Point2f>> svgVertices{};
	if (SVGParser::GetVerticesFromSvgFile("./Resources/Level/Level.svg", svgVertices))
	{
		m_Vertices = svgVertices[0];
		std::cout << "Level succesfully loaded from svg" << std::endl;
	}
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	delete m_pForegroundTexture;
	m_pBackgroundTexture = nullptr;
	m_pForegroundTexture = nullptr;
}

void Level::DrawBackground() const
{
	m_pBackgroundTexture->Draw();
}

void Level::DrawForeground() const
{
	m_pForegroundTexture->Draw(Rectf{ 200, 190, m_pForegroundTexture->GetWidth(), m_pForegroundTexture->GetHeight() });
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	if (DoRaycast(actorShape, hitInfo))
	{
		actorVelocity.y = 0;
		actorShape.bottom = hitInfo.intersectPoint.y;
	}
}

bool Level::IsOnGround(const Rectf& actorShape) const
{
	utils::HitInfo hitInfo{};
	return DoRaycast(actorShape, hitInfo);
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

bool Level::DoRaycast(const Rectf& actorShape, utils::HitInfo& hitInfo) const
{
	Point2f rectCentreTop{ utils::GetRectCentreTop(actorShape) };
	Point2f rectCentreBottom{ rectCentreTop.x, rectCentreTop.y - actorShape.height - 1 };
	return utils::Raycast(m_Vertices, rectCentreTop, rectCentreBottom, hitInfo);
}
