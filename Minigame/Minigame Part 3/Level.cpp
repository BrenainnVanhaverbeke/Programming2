#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "SVGParser.h"
#include "Platform.h"
#include <iostream>

Level::Level()
	: m_pBackgroundTexture{ new Texture("Resources/Images/background.png") }
	, m_pForegroundTexture{ new Texture("Resources/Images/fence.png") }
	, m_pEndSignTexture{ new Texture("Resources/Images/EndSign.png") }
	, m_Boundaries{ 0.0f, 0.0f, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight() }
	, m_FenceBottomLeft{ 200.0f, 190.0f }
	, m_EndSignShape{ 730, 224, m_pEndSignTexture->GetWidth(), m_pEndSignTexture->GetHeight() }
{
	std::vector<std::vector<Point2f>> svgVertices{};
	if (SVGParser::GetVerticesFromSvgFile("./Resources/Level/Level.svg", svgVertices))
		m_Vertices = svgVertices[0];
	else
	{
		std::cout << "Level failed to load from svg" << std::endl;
		InitialiseVertices();
	}
	InitialisePlatforms();
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	delete m_pForegroundTexture;
	delete m_pEndSignTexture;
	m_pBackgroundTexture = nullptr;
	m_pForegroundTexture = nullptr;
	m_pEndSignTexture = nullptr;
	for (Platform* platform : m_pPlatforms)
		delete platform;
	m_pPlatforms.clear();
}

void Level::DrawBackground() const
{
	m_pBackgroundTexture->Draw();
	for (Platform* platform : m_pPlatforms)
		platform->Draw();
}

void Level::DrawForeground() const
{
	m_pForegroundTexture->Draw(m_FenceBottomLeft);
	m_pEndSignTexture->Draw(m_EndSignShape);
}

void Level::DrawGameOver() const
{
	Color4f transparentBlack{ 0.0f, 0.0f, 0.0f, 0.5f };
	utils::SetColor(transparentBlack);
	utils::FillRect(m_Boundaries);
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	if (DoRaycast(actorShape, hitInfo))
	{
		actorVelocity.y = 0;
		actorShape.bottom = hitInfo.intersectPoint.y;
	}
	else
	{
		for (Platform* platform : m_pPlatforms)
			platform->HandleCollision(actorShape, actorVelocity);
	}
}

bool Level::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	if (DoRaycast(actorShape, hitInfo))
		return true;
	for (Platform* platform : m_pPlatforms)
	{
		if (platform->IsOnGround(actorShape, actorVelocity))
			return true;
	}
	return false;
}

bool Level::HasReachedEnd(const Rectf& actorShape) const
{
	return utils::IsOverlapping(m_EndSignShape, actorShape);
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

// Deprecated, left in as backup.
void Level::InitialiseVertices()
{
	m_Vertices.push_back(Point2f{ 0, 0 });
	m_Vertices.push_back(Point2f{ 0, 190 });
	m_Vertices.push_back(Point2f{ 340, 190 });
	m_Vertices.push_back(Point2f{ 408, 124 });
	m_Vertices.push_back(Point2f{ 560, 124 });
	m_Vertices.push_back(Point2f{ 660, 224 });
	m_Vertices.push_back(Point2f{ 846, 224 });
	m_Vertices.push_back(Point2f{ 846, 0 });
	m_Vertices.push_back(Point2f{ 0, 0 });
}

void Level::InitialisePlatforms()
{
	m_pPlatforms.push_back(new Platform(Point2f{ 240.0f, 320.0f }));
	m_pPlatforms.push_back(new Platform(Point2f{ 390.0f, 280.0f }));
}

bool Level::DoRaycast(const Rectf& actorShape, utils::HitInfo& hitInfo) const
{
	Point2f rectCentreTop{ utils::GetRectCentreTop(actorShape) };
	Point2f rectCentreBottom{ rectCentreTop.x, rectCentreTop.y - actorShape.height - 1 };
	return utils::Raycast(m_Vertices, rectCentreTop, rectCentreBottom, hitInfo);
}
